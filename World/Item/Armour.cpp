#include "Armour.h"

#include <assert.h>

using namespace ArmourDefinitions;

Armour::Armour(std::string name,
               int armourClassBase,
               ArmourTypeEnum eArmourType,
               int minStrength) :
    Equipment(name, ItemDefinitions::eArmour),
    m_armouClassBase(armourClassBase),
    m_eArmourType(eArmourType),
    m_minStrength(minStrength)
{
}

Armour::~Armour()
{
}

int Armour::GetArmourClassBase() const
{
    return m_armouClassBase;
}

int Armour::GetMinStrength() const
{
    return m_minStrength;
}

int Armour::GetMaxDexBonus() const
{
    int maxDexBonus;

    switch(m_eArmourType)
    {
    case eLightArmour:
        maxDexBonus = 100;
        break;
    case eMediumArmour:
        maxDexBonus = 2;
        break;
    case eHeavyArmour:
    case eNaturalArmour:
        maxDexBonus = 0;
        break;
    default:
        maxDexBonus = -1;
        assert(false);
    }

    return maxDexBonus;
}
