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
