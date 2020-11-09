#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Definitions/ItemDefinitions.h"
#include "Definitions/PlayerDefinitions.h"

using namespace PlayerDefinitions;

class Key;

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

    bool HasKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType) const;
    void AddKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType);
    bool UseKey(ItemDefinitions::KeyDoorTypeEnum keyDoorType);

    void HasPotion(ItemDefinitions::PotionTypeEnum) const;
    void AddPotion(ItemDefinitions::PotionTypeEnum);
    void UsePotion(ItemDefinitions::PotionTypeEnum);

private:
    ClassEnum m_eClass;
    RaceEnum m_eRace;

    std::map<ItemDefinitions::KeyDoorTypeEnum, int> m_keys;
    std::map<ItemDefinitions::PotionTypeEnum, int> m_potions;
};

#endif // PLAYER_H
