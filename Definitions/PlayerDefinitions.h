#ifndef PLAYERDEFINITIONS_H
#define PLAYERDEFINITIONS_H

#include <string>
#include <vector>

namespace PlayerDefinitions
{
    enum ClassEnum { eBarbarian = 0, eFighter, eRogue };

    enum RaceEnum { eDwarf = 0, eElf, eHuman };

    const std::vector<std::vector<int>> RACE_ABILITY_SCORE = {
        { 2, 0, 2, 0, 0, 0}, // Dwarf
        { 0, 2, 0, 1, 0, 0}, // Elf
        { 1, 1, 1, 1, 1, 1}, // Human
    };

    const std::vector<std::vector<int>> CLASS_ABILITY_SCORE = {
        { 15, 13, 14, 8, 10, 12}, // Barbarian
        { 15, 14, 13, 12, 10, 8}, // Fighter
        { 12, 15, 10, 14, 8, 13}, // Rogue
    };

    const std::vector<int> BASE_HEALTH = {
        12, // Barbarian
        10, // Fighter
        8,  // Rogue
    };

    const std::vector<std::string> SPRITES = {
        "LinkLeft.png",
        "LinkBack.png",
        "LinkRight.png",
        "LinkForward.png",
    };
}

#endif // PLAYERDEFINITIONS_H
