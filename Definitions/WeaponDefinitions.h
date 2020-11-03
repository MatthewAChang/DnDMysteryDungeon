#ifndef WEAPONDEFINITIONS_H
#define WEAPONDEFINITIONS_H

#include "CharacterDefinitions.h"

#include <vector>
#include <string>

namespace WeaponDefinitions
{
    enum WeaponEnum { eNone = 0, eGreataxe, eJavelin, eLightCrossbow, eLongbow, eLongsword, eScimitar, eShortbow, eShortsword };

    enum RangeEnum { eShort = 0, eMedium, eLong };

    const std::vector<std::string> WEAPON_NAME = {
        {"None"},
        {"Greataxe"},
        {"Javelin"},
        {"Light Crossbow"},
        {"Longbow"},
        {"Longsword"},
        {"Scimitar"},
        {"Shortbow"},
        {"Shortsword"}
    };

    const std::vector<std::pair<int, int>> WEAPON_DAMAGES = {
        {1, 4},
        {1, 12},
        {1, 6},
        {1, 8},
        {1, 8},
        {1, 8},
        {1, 6},
        {1, 6},
        {1, 6},
    };

    const std::vector<CharacterDefinitions::AbilityEnum> WEAPON_ABILITY_MODIFIER = {
        CharacterDefinitions::eStrength,
        CharacterDefinitions::eStrength,
        CharacterDefinitions::eStrength,
        CharacterDefinitions::eDexterity,
        CharacterDefinitions::eDexterity,
        CharacterDefinitions::eStrength,
        CharacterDefinitions::eDexterity,
        CharacterDefinitions::eDexterity,
        CharacterDefinitions::eStrength,
    };

    const std::vector<RangeEnum> WEAPON_RANGE = {
        eShort,
        eShort,
        eMedium,
        eLong,
        eLong,
        eShort,
        eShort,
        eLong,
        eShort,
    };

    const std::vector<bool> WEAPON_TWO_HANDED = {
        false,
        true,
        false,
        true,
        true,
        false,
        false,
        true,
        false,
    };
}

#endif // WEAPONDEFINITIONS_H
