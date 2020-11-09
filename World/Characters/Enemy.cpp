#include "Enemy.h"

Enemy::Enemy(int id,
             std::string name,
             std::vector<int> abilityScores,
             int health,
             std::shared_ptr<Armour> armour,
             std::shared_ptr<Weapon> weapon,
             Location location,
             CharacterDefinitions::EnemyStateEnum state) :
    Character(id, name, abilityScores, health, armour, weapon, location),
    m_state(state),
    m_target(nullptr)
{
}
