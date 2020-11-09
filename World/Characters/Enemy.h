#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Armour;
class Weapon;

class Enemy: public Character
{
public:
    Enemy(int id,
          std::string name,
          std::vector<int> abilityScores,
          int health,
          std::shared_ptr<Armour> armour,
          std::shared_ptr<Weapon> weapon,
          Location location,
          CharacterDefinitions::EnemyStateEnum state);
    ~Enemy() {}

    void SetState(CharacterDefinitions::EnemyStateEnum state) { m_state = state; }
    CharacterDefinitions::EnemyStateEnum GetState() const { return m_state; }

    void SetTarget(std::shared_ptr<Character> target) { m_target = target; }
    std::shared_ptr<Character> GetTarget() const { return m_target; }

    CharacterDefinitions::EnemyStateEnum m_state;
    std::shared_ptr<Character> m_target;
};

#endif // ENEMY_H
