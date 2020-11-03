#ifndef ENEMYDEFINITIONS_H
#define ENEMYDEFINITIONS_H

#include "ArmourDefinitions.h"
#include "WeaponDefinitions.h"

#include <vector>
#include <string>

namespace EnemyDefinitions
{
    enum EnemyEnum { eGoblin = 0, eGoblinBoss };

    const std::vector<std::string> ENEMY_NAME = {
        "Goblin",
        "Goblin Archer",
        "Goblin Boss"
    };

    const std::vector<std::pair<int, int>> ENEMY_HEALTHS = {
        { 2, 6 },
        { 2, 6 },
        { 6, 6 }
    };

    const std::vector<std::vector<int>> ENEMY_ABILITY_SCORE = {
        { 8, 14, 10, 10, 8, 8 },
        { 8, 14, 10, 10, 8, 8 },
        { 10, 14, 10, 10, 8, 10 }
    };

    const std::vector<ArmourDefinitions::ArmourEnum> ENEMY_ARMOUR = {
        ArmourDefinitions::eLeather,
        ArmourDefinitions::eLeather,
        ArmourDefinitions::eChainShirt
    };

    const std::vector<WeaponDefinitions::WeaponEnum> ENEMY_WEAPON = {
        WeaponDefinitions::eScimitar,
        WeaponDefinitions::eShortbow,
        WeaponDefinitions::eScimitar
    };

    const std::vector<bool> ENEMY_SHIELD = {
        true,
        false,
        true
    };
}

#endif // ENEMYDEFINITIONS_H
