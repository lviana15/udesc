module pokemon {
  import basicSpells.* from "../spells/basicSpells"

  type PokemonType = Water | Fire | Grass | Eletric
  type DamageModifier = SuperEffective | NotVeryEffective | Normal

  type Pokemon = {
    name: str,
    hp: int,
    speed: int,
    team: str,
    pokemon_type: PokemonType
  }

  type Attack = Option[{ attacker: Pokemon, receiver: Pokemon, attack: str, damage: int }]

  pure val POKEMONS = Set(
    { name: "Squirtle", hp: 44, speed: 43, team: "", pokemon_type: Water },
    { name: "Bulbasaur", hp: 45, speed: 45, team: "", pokemon_type: Grass },
    { name: "Charmander", hp: 39, speed: 65, team: "", pokemon_type: Fire },
    { name: "Zapdos", hp: 90, speed: 100, team: "", pokemon_type: Eletric }
  )

  var pokemons: str -> Pokemon
  var next_team: str
  var next_attack: Attack

  pure def other_team(team: str): str = if (team == "A") "B" else "A"

  pure def damage(p: Pokemon, d: int): Pokemon = {
    { ...p, hp: p.hp - d }
  }

  // Atualizado com tipo eletrico
  pure def damage_modifier(attacker: Pokemon, receiver: Pokemon): DamageModifier = {
    match attacker.pokemon_type {
      | Water => match receiver.pokemon_type {
        | Water => NotVeryEffective
        | Fire => SuperEffective
        | Grass => NotVeryEffective
        | Eletric => Normal
      }
      | Fire => match receiver.pokemon_type {
        | Water => NotVeryEffective
        | Fire => NotVeryEffective
        | Grass => SuperEffective
        | Eletric => Normal
      }
      | Grass => match receiver.pokemon_type {
        | Water => SuperEffective
        | Fire => NotVeryEffective
        | Grass => NotVeryEffective
        | Eletric => Normal
      }
      | Eletric => match receiver.pokemon_type {
        | Water => SuperEffective
        | Fire => Normal
        | Grass => NotVeryEffective
        | Eletric => NotVeryEffective
      }
    }
  }

  action tackle(receiver: Pokemon): bool = all {
    pokemons' = pokemons.setBy(receiver.team, p => p.damage(10))
  }

  action elemental_attack(attacker: Pokemon, receiver: Pokemon): bool = {
    val base_damage = 10
    val actual_damage = match damage_modifier(attacker, receiver) {
      | SuperEffective => base_damage * 2
      | NotVeryEffective => base_damage / 2
      | Normal => base_damage
    }

    pokemons' = pokemons.setBy(receiver.team, p => p.damage(actual_damage))
  }

  // Agora verifica elementos do atacante e receptor para utilizar ataque mais efetivo
  action attack(attacker: Pokemon, receiver: Pokemon): bool = {
    all {
      attacker != receiver,
      attacker.hp > 0,
      receiver.hp > 0,
      match (damage_modifier(attacker, receiver)) {
        | SuperEffective => elemental_attack(attacker, receiver)
        | _ => tackle(receiver)
      },
    }
  }

  action init = {
    nondet team_A_pokemon = POKEMONS.oneOf()
    nondet team_B_pokemon = POKEMONS.oneOf()
    all {
      pokemons' = Map(
        "A" -> { ...team_A_pokemon, team: "A" },
        "B" -> { ...team_B_pokemon, team: "B" }
      ),
      next_team' = if (team_A_pokemon.speed > team_B_pokemon.speed) "A" else "B",
      next_attack' = None,
    }
  }

  action step = {
    val attacker = pokemons.get(next_team)
    val receiver = pokemons.get(other_team(next_team))
    all {
      attack(attacker, receiver),
      next_team' = other_team(next_team),
      next_attack' = match (damage_modifier(attacker, receiver)) {
        | SuperEffective => Some({ attacker: attacker, receiver: receiver, attack: "elemental attack", damage: 20 })
        | _ => Some({ attacker: attacker, receiver: receiver, attack: "tackle", damage: 10 })
      },
    }
  }

  val inv = pokemons.values().forall(p => p.hp > 0)

  // Invariante sem condição de vitória
  // Nesse caso invariante é violada quando pokemon de grama tem HP inicial maior que pokemon de fogo
  // ou caso diferença em HP inicial é menor que ataque e pokemon de grama ataca primeiro
  val fire_beats_grass = all {
    val fire_pokemons = pokemons.values().filter(p => p.pokemon_type == Fire)
    val grass_pokemons = pokemons.values().filter(p => p.pokemon_type == Grass)
    grass_pokemons.forall(gp => {
      fire_pokemons.exists(fp => fp.hp > gp.hp)
    })
  }

  // Caso tivessemos condição de vitória invariante teria definição diferente
  // E seria violada quando pokemon de fogo usasse 'tackle' ao inves de ataque elemental mesmo tendo vantagem
  // Então alteramos action de attack para usar ataque elemental quando tiver vantagem
}
