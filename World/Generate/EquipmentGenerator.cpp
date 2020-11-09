#include "EquipmentGenerator.h"

#include "World/Item/Armour.h"
#include "World/Item/Weapon.h"

std::shared_ptr<Armour> EquipmentGenerator::GenerateArmour(ArmourDefinitions::ArmourEnum eArmour)
{
    using namespace ArmourDefinitions;

    auto armour = std::make_shared<Armour>(ARMOUR_NAME[eArmour],
                                           ARMOUR_CLASS_BASE[eArmour],
                                           ARMOUR_TYPE[eArmour],
                                           ARMOUR_MIN_STRENGTH[eArmour]);

    return armour;
}

std::shared_ptr<Weapon> EquipmentGenerator::GenerateWeapon(WeaponDefinitions::WeaponEnum eWeapon)
{
    using namespace WeaponDefinitions;

    auto weapon = std::make_shared<Weapon>(WEAPON_NAME[eWeapon],
                                           WEAPON_DAMAGES[eWeapon],
                                           WEAPON_ABILITY_MODIFIER[eWeapon],
                                           WEAPON_RANGE[eWeapon],
                                           WEAPON_TWO_HANDED[eWeapon]);

    return weapon;
}
