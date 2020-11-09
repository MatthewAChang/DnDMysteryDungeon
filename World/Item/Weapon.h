#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"
#include "Definitions/CharacterDefinitions.h"
#include "Definitions/WeaponDefinitions.h"

class Weapon: public Equipment
{
public:
    Weapon(std::string name,
           std::pair<int, int> damages,
           CharacterDefinitions::AbilityEnum abilityModifier,
           WeaponDefinitions::RangeEnum range,
           bool twoHanded = false);
    ~Weapon();

    int GetDamage() const;
    int GetAbiltyModifier() const { return m_abilityModifier; }
    int GetRange() const { return m_range; }
    bool IsTwoHanded() const { return m_twoHanded; }

private:
    std::pair<int, int> m_damages;
    CharacterDefinitions::AbilityEnum m_abilityModifier;
    WeaponDefinitions::RangeEnum m_range;
    bool m_twoHanded;
};

#endif // WEAPON_H
