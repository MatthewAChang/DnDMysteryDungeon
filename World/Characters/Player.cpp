#include "Player.h"

Player::Player(int id,
               std::string name,
               ClassEnum eClass,
               RaceEnum eRace,
               std::vector<int> abilityScores,
               int health,
               std::vector<std::string> sprites) :
    Character(id, name, abilityScores, health, sprites),
    m_eClass(eClass),
    m_eRace(eRace)
{
}

Player::~Player()
{

}

bool Player::HasKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType) const
{
    return m_keys.find(keyDoorType) != m_keys.end();
}

void Player::AddKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType)
{
    auto it = m_keys.find(keyDoorType);
    if (it != m_keys.end())
    {
        ++it->second;
    }
    else
    {
        m_keys[keyDoorType] = 1;
    }
}

bool Player::UseKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType)
{
    auto it = m_keys.find(keyDoorType);
    if (it != m_keys.end())
    {
        --it->second;
        if (it->second <= 0)
        {
            m_keys.erase(it);
        }

        return true;
    }

    return false;
}
