#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Definitions/PlayerDefinitions.h"

using namespace PlayerDefinitions;

class Player: public Character
{
public:
    Player(int id,
           std::string name,
           ClassEnum eClass,
           RaceEnum eRace,
           std::vector<int> abilityScores,
           int health,
           std::vector<std::string> sprites);
    ~Player();

    ClassEnum GetClass() const { return m_eClass; }
    RaceEnum GetRace() const { return m_eRace; }

    virtual bool IsPlayer() const override { return true; }
    virtual void Action() override {}

private:
    ClassEnum m_eClass;
    RaceEnum m_eRace;
};

#endif // PLAYER_H
