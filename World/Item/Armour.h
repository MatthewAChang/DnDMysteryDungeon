#ifndef ARMOUR_H
#define ARMOUR_H

#include "Equipment.h"
#include "Definitions/ArmourDefinitions.h"

class Armour: public Equipment
{
public:
    Armour(std::string name,
           int armourClassBase,
           ArmourDefinitions::ArmourTypeEnum eArmourType,
           int minStrength);
    ~Armour();

    int GetArmourClassBase() const;
    int GetMinStrength() const;

    int GetMaxDexBonus() const;

private:
    int m_armouClassBase;
    ArmourDefinitions::ArmourTypeEnum m_eArmourType;
    int m_minStrength;
};

#endif // ARMOUR_H
