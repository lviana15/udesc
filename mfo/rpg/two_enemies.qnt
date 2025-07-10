module rpg {
  import basicSpells.* from "./spells/basicSpells"

    type Class = Priest | Bard | Necro | Enemy
    type Action = Attack | RemoveStun | Heal | Buff | Skill | Stun | StartRitual | FinishRitual

    type Status = Alive | Dead | Stunned

    type Creature = {
        name: str,
        maxHealth: int,
        health: int,
        class: Class,
        status: Status
    }

    type LastAction = Option[{ 
        character: Creature,
        charAction: Action,
        target: Option[Creature],
        damage: Option[int],
        heal: Option[int]
    }]

    pure val CREATURES = Map(
        "Priest"  -> { name: "Priest",  maxHealth: 20, health: 20, status: Alive, class: Priest },
        "Bard"    -> { name: "Bard",    maxHealth: 20, health: 20, status: Alive, class: Bard },
        "Necro"   -> { name: "Necro",   maxHealth: 20, health: 20, status: Alive, class: Necro },
        "Enemy 1" -> { name: "Enemy 1", maxHealth: 90, health: 90, status: Alive, class: Enemy },
        "Enemy 2" -> { name: "Enemy 2", maxHealth: 90, health: 90, status: Alive, class: Enemy }
    )

    pure def damage(c: Creature, dmg: int): Creature = {
        val newHealth = c.health - dmg
        val newStatus = if (newHealth <= 0) { Dead } else { c.status }
        { ...c, health: newHealth, status: newStatus }
    }

    pure def heal(c: Creature, healAmount: int): Creature = {
        val newHealth = min(c.health + healAmount, c.maxHealth)
        { ...c, health: newHealth }
    }

    pure def nextCharTurn(turnOrder: List[(str, int)], turnIndex: int): (str, int) = {
        if (turnIndex + 1 < turnOrder.length()) {
            turnOrder[turnIndex + 1]
        } else {
            turnOrder[0]
        }
    }

    var characters: str -> Creature
    var lastAction: LastAction
    var isBardBuffActive: bool
    var ritual: Option[{ initiator: str, turnsLeft: int }]
    var turnOrder: List[(str, int)]
    var turnIndex: int

    action AttackAction(attacker: Creature, target: Creature): bool = {
        val dmg = if (isBardBuffActive) { 30 } else { 10 }
        val updatedTarget = damage(target, dmg)
        
        all { 
            attacker.status == Alive,
            target.status == Alive,
            match (attacker.class) {
                | Enemy => target.class != Enemy
                | _ => target.class == Enemy
            },

            isBardBuffActive' = false,
            characters' = characters.set(target.name, updatedTarget),
            lastAction' = Some({ 
                    character: attacker,
                    charAction: Attack,
                    target: Some(updatedTarget),
                    damage: Some(dmg),
                    heal: None
                })
        }
    }

    action HealAction(caster: Creature): bool = {
        val updatedCharacters =
            characters.keys().mapBy(charName =>
                val char = characters.get(charName)
                
                if (char.class != Enemy and char.status != Dead and char.health < char.maxHealth) {
                    val toHeal = if (char.health + 10 > char.maxHealth) { 
                        (char.maxHealth - char.health) 
                    } else { 
                        10 
                    }
                    heal(char, toHeal)
                } else {
                    char
                }
            )

        all {
            caster.class == Priest,
            caster.status == Alive,
            characters.values().filter(c => c.class != Enemy and c.status != Dead and c.health < c.maxHealth).exists(c => c.health < c.maxHealth),

            isBardBuffActive' = isBardBuffActive,
            characters' = updatedCharacters,

            lastAction' = Some({
                    character: caster,
                    charAction: Heal,
                    target: None,
                    damage: None,
                    heal: None
                })
        }
    }

    action BuffAction(caster: Creature): bool = {
        val nextChar = characters.get(nextCharTurn(turnOrder, turnIndex)._1)
        
        all {
            caster.class == Bard,
            caster.status == Alive,
            nextChar.class == Necro,

            isBardBuffActive' = true,
            characters' = characters,
            lastAction' = Some({
                    character: caster,
                    charAction: Buff,
                    target: None,
                    damage: None,
                    heal: None
                })
        }
    }

    action BloodLanceAction(caster: Creature, target: Creature): bool = {
        val dmg = if (isBardBuffActive) { 60 } else { 20 }
        val updatedCaster = damage(caster, 10)
        val updatedTarget = damage(target, dmg)

        all {
            caster.class == Necro,
            caster.status == Alive,
            target.class == Enemy,
            target.status == Alive,

            characters' = characters
                .set(caster.name, updatedCaster)
                .set(target.name, updatedTarget),

            isBardBuffActive' = false,
            lastAction' = Some({
                character: updatedCaster,
                charAction: Skill,
                target: Some(updatedTarget),
                damage: Some(dmg),
                heal: None
            })
        }
    }

    action StunAction(caster: Creature, target: Creature): bool = {
        all {
            caster.class == Enemy,
            caster.status == Alive,
            target.status == Alive,
            target.class != Enemy,

            isBardBuffActive' = isBardBuffActive,
            characters' = characters.set(target.name, { ...target, status: Stunned }),
            lastAction' = Some({ 
                    character: caster,
                    charAction: Stun,
                    target: Some(target),
                    damage: None,
                    heal: None,
                })
        }
    }

    action RemoveStunAction(caster: Creature, target: Creature): bool = {
        all {
            caster.class != Enemy,
            caster.status == Alive,
            target.status == Stunned,

            isBardBuffActive' = isBardBuffActive,
            characters' = characters.set(target.name, { ...target, status: Alive }),
            lastAction' = Some({ 
                    character: caster,
                    charAction: RemoveStun,
                    target: Some(target),
                    damage: None,
                    heal: None
                })
        }
    }

    action StartRitualAction(initiator: Creature): bool = {
        all {
            ritual == None,
            initiator.class == Enemy,
            initiator.status == Alive,

            isBardBuffActive' = isBardBuffActive,
            characters'       = characters,
            
            ritual' = Some({ initiator: initiator.name, turnsLeft: 3}),
            lastAction' = Some({
                    character: initiator,
                    charAction: StartRitual,
                    target: None,
                    damage: None,
                    heal: None
                })
        }
    }

    action ProgressRitualAction(caster: Creature): bool = {
        val current_ritual = ritual.unwrap()
        all {
            ritual != None,
            current_ritual.initiator == caster.name,
            current_ritual.turnsLeft > 0,

            characters'       = characters,
            isBardBuffActive' = isBardBuffActive,

            ritual' = Some({ 
                ...current_ritual, 
                turnsLeft: current_ritual.turnsLeft - 1
            }),
            lastAction' = Some({
                    character: caster,
                    charAction: StartRitual,
                    target: None,
                    damage: None,
                    heal: None
                })
        }
    }

    action EndRitualAction(caster: Creature): bool = {
        val current_ritual = ritual.unwrap()
        val curr_chars     = characters.keys()

        val updatedCharacters = curr_chars.mapBy(charName =>
            val char = characters.get(charName)
            if (char.class != Enemy) {
                { ...char, health: 0, status: Dead }
            } else {
                { ...char }
            }
        )

        all {
            ritual != None,
            current_ritual.initiator == caster.name,
            current_ritual.turnsLeft == 0,
            caster.status != Dead,

            ritual' = None,
            characters' = updatedCharacters,
            isBardBuffActive' = isBardBuffActive,
            lastAction' = Some({ 
                    character: caster,
                    charAction: FinishRitual,
                    target: None,
                    damage: None,
                    heal: None
                })
        }
    }

    action EnemyTurn(enemy: Creature): bool = {
        nondet target = characters.values().filter(c => c.class != Enemy).oneOf()

        match ritual {
            | None => StartRitualAction(enemy)
            | Some(current_ritual) =>
                if (current_ritual.turnsLeft > 0) {
                    all{
                        ritual' = Some({ 
                            ...current_ritual, 
                            turnsLeft: current_ritual.turnsLeft - 1
                        }),
                        any {
                            StunAction(enemy, target),
                            AttackAction(enemy, target),
                        }
                    }
                } else {
                    EndRitualAction(enemy)
                }
        }
    }

    action PriestTurn(priest: Creature): bool = {
        nondet allyTarget = characters.values().filter(c => c.class != Enemy).oneOf()
        nondet target = characters.values().filter(c => c.class == Enemy).oneOf()

        if (characters.values().filter(c => c.class != Enemy).exists(c => c.health < c.maxHealth)){
            HealAction(priest)
        } else {
            any {
                RemoveStunAction(priest, allyTarget),
                AttackAction(priest, target),
            }
        }
    }

    action BardTurn(bard: Creature): bool = {
        nondet allyTarget = characters.values().filter(c => c.class != Enemy).oneOf()
        nondet target = characters.values().filter(c => c.class == Enemy).oneOf()

        if (characters.values().filter(c => c.class != Enemy).exists(c => c.status == Stunned)) {
            RemoveStunAction(bard, allyTarget)
        } else {
            any {
                AttackAction(bard, target),
                BuffAction(bard)
            }
        }
    }

    action NecroTurn (necro: Creature): bool = {
        nondet allyTarget = characters.values().filter(c => c.class != Enemy).oneOf()
        nondet target = characters.values().filter(c => c.class == Enemy).oneOf()

        val nextTurnChar = nextCharTurn(turnOrder, turnIndex)
        val nextChar = characters.get(nextTurnChar._1)

        if ((target.health <= 30 or isBardBuffActive) and necro.health > 10 and nextChar.class != Enemy) {
            BloodLanceAction(necro, target)
        } else {
            any {
                RemoveStunAction(necro, allyTarget),
                AttackAction(necro, target),
            }
        }
    }

    action init = {
        val initialCharacters = CREATURES
        
        nondet bardInitiative = 1.to(20).oneOf()
        nondet priestInitiative = 1.to(20).oneOf()
        nondet necroInitiative = 1.to(20).oneOf()
        nondet enemy1Initiative = 1.to(20).oneOf()
        nondet enemy2Initiative = 1.to(20).oneOf()

        val initiativeOrder = 
            [
                ("Bard",  bardInitiative), 
                ("Priest", priestInitiative), 
                ("Necro", necroInitiative), 
                ("Enemy 1", enemy1Initiative),
                ("Enemy 2", enemy2Initiative)
            ].sortList((a, b) => a._2 > b._2 )
            
        all {
            turnOrder' = initiativeOrder,
            turnIndex' = 0,
            characters' = initialCharacters,
            lastAction' = None,
            isBardBuffActive' = false,
            ritual' = None
        }
    }

    action step = {
        val currentCharacter = characters.get(turnOrder[turnIndex]._1)

        all {
            turnOrder' = turnOrder,
            match currentCharacter.status {
                | Alive => turnIndex' = (turnIndex + 1) % turnOrder.length()
                | Dead => turnIndex' = turnIndex
                | Stunned => turnIndex' = (turnIndex + 1) % turnOrder.length()
            },
            match currentCharacter.class {
                | Priest => all {
                    PriestTurn(currentCharacter),
                    ritual' = ritual,
                  }
                | Bard => all {
                    BardTurn(currentCharacter),
                    ritual' = ritual,
                  }
                | Necro => all {
                    NecroTurn(currentCharacter),
                    ritual' = ritual,  
                  }
                | Enemy => EnemyTurn(currentCharacter)
            },
        }
    }

    val enemyStaysAlive =
        characters
            .values()
            .filter(c => c.class == Enemy)
            .exists(c => c.status != Dead)

    val allCharsAlive = 
        characters
            .values()
            .filter(c => c.class != Enemy)
            .forall(c => c.status != Dead)

    val bardStaysAlive = 
        characters.values().filter(c => c.class == Bard).exists(c => c.status != Dead)
}
