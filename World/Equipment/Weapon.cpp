#include "Weapon.h"

#include <time.h>

Weapon::Weapon(std::string name,
               std::pair<int, int> damages,
               CharacterDefinitions::AbilityEnum abilityModifier,
               WeaponDefinitions::RangeEnum range,
               bool twoHanded) :
    Equipment(name),
    m_damages(damages),
    m_abilityModifier(abilityModifier),
    m_range(range),
    m_twoHanded(twoHanded)
{
    srand(static_cast<unsigned int>(time(NULL)));
}

Weapon::~Weapon()
{
}

int Weapon::GetDamage() const
{
    int damage = 0;

    for (int i = 0; i < m_damages.first; ++i)
    {
        damage += rand() % m_damages.second + 1;
    }

    return damage;
}
