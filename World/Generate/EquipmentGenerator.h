#ifndef WEAPONGENERATOR_H
#define WEAPONGENERATOR_H

#include "Definitions/ArmourDefinitions.h"
#include "Definitions/WeaponDefinitions.h"

#include <memory>

class Armour;
class Weapon;

class EquipmentGenerator
{
public:
    EquipmentGenerator() {}
    ~EquipmentGenerator() {}

    std::shared_ptr<Armour> GenerateArmour(ArmourDefinitions::ArmourEnum eArmour);
    std::shared_ptr<Weapon> GenerateWeapon(WeaponDefinitions::WeaponEnum eWeapon);
};

#endif // WEAPONGENERATOR_H
