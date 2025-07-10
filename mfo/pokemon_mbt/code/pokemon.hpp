#include <map>
#include <string>
using namespace std;

enum class PokemonType {
  Water,
  Fire,
  Grass,
  Electric,
};

enum class DamageModifier {
  NotVeryEffective,
  Normal,
  SuperEffective,
};

struct Pokemon {
  string name;
  int hp;
  int speed;
  string team;
  PokemonType pokemon_type;
};

DamageModifier damage_modifier(Pokemon &attacker, Pokemon &receiver) {
  switch (attacker.pokemon_type) {
    case PokemonType::Water:
      switch (receiver.pokemon_type) {
        case PokemonType::Water:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Fire:
          return DamageModifier::SuperEffective;
        case PokemonType::Grass:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Electric:
          return DamageModifier::Normal;
      }
      break;
    case PokemonType::Fire:
      switch (receiver.pokemon_type) {
        case PokemonType::Water:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Fire:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Grass:
          return DamageModifier::SuperEffective;
        case PokemonType::Electric:
          return DamageModifier::Normal;
      }
      break;
    case PokemonType::Grass:
      switch (receiver.pokemon_type) {
        case PokemonType::Water:
          return DamageModifier::SuperEffective;
        case PokemonType::Fire:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Grass:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Electric:
          return DamageModifier::Normal;
      }
      break;
    case PokemonType::Electric:
      switch (receiver.pokemon_type) {
        case PokemonType::Water:
          return DamageModifier::SuperEffective;
        case PokemonType::Fire:
          return DamageModifier::Normal;
        case PokemonType::Grass:
          return DamageModifier::NotVeryEffective;
        case PokemonType::Electric:
          return DamageModifier::NotVeryEffective;
      }
      break;
  }

  return DamageModifier::Normal;
}

void tackle(Pokemon &attacker, Pokemon &receiver, int damage) {
  receiver.hp -= damage;
}

void elemental_attack(Pokemon &attacker, Pokemon &receiver, int damage) {
  DamageModifier modifier = damage_modifier(attacker, receiver);
  switch (modifier) {
    case DamageModifier::NotVeryEffective:
      damage /= 2;
      break;
    case DamageModifier::Normal:
      break;
    case DamageModifier::SuperEffective:
      damage *= 2;
      break;
  }

  receiver.hp -= damage;
}
