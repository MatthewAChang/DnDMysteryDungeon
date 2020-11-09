#ifndef HELPER_H
#define HELPER_H

#include "AStarSearchAlgorithm.h"
#include "Definitions/CharacterDefinitions.h"
#include "Definitions/TypeDefinitions.h"

#include <stdlib.h>
#include <time.h>

class Helper
{
public:
    static Helper& GetInstance()
    {
        static Helper instance;

        return instance;
    }

    Helper(Helper const&) = delete;
    void operator=(Helper const&) = delete;

    int GetAbilityScoreModifier(int abilityScore) const
    {
        return (abilityScore / 2) + -5;
    }

    int Roll(int d1, int d2) const
    {
        int value = 0;

        for (int i = 0; i < d1; ++i)
        {
            value += rand() % d2 + 1;
        }

        return value;
    }

    MapDefinitions::DirectionEnum GetRandomDirection() const
    {
        return static_cast<MapDefinitions::DirectionEnum>(rand() % 4 + 1);
    }

    MapDefinitions::DirectionEnum FindNextMove(const LevelTerrainMap& terrainMap,
                                               const LevelInteractableMap& interactableMap,
                                               const Location& src,
                                               const Location& dest)
    {
        using namespace CharacterDefinitions;

        Location move = AStar::FindNextMove(terrainMap, interactableMap, LevelCharacterMap(), {src.second, src.first}, {dest.second, dest.first});

        return GetDirectionToMove(src, move);
    }

    MapDefinitions::DirectionEnum FindNextMove(const LevelTerrainMap& terrainMap,
                                               const LevelInteractableMap& interactableMap,
                                               const LevelCharacterMap& characterMap,
                                               const Location& src,
                                               const Location& dest)
    {


        Location move = AStar::FindNextMove(terrainMap, interactableMap, characterMap, {src.second, src.first}, {dest.second, dest.first});

        return GetDirectionToMove(src, move);
    }

private:
    Helper()
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }

    ~Helper() {}

    MapDefinitions::DirectionEnum GetDirectionToMove(Location src, Location move) const
    {
        using namespace MapDefinitions;

        Location moveFlipped = {move.second, move.first};

        if (moveFlipped.first + 1 == src.first)
        {
            return eWest;
        }

        if (moveFlipped.second + 1 == src.second)
        {
            return eNorth;
        }

        if (moveFlipped.first - 1 == src.first)
        {
            return eEast;
        }

        if (moveFlipped.second - 1 == src.second)
        {
            return eSouth;
        }

        return eNull;
    }
};

#endif // HELPER_H
