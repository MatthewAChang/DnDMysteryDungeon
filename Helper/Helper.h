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

    CharacterDefinitions::DirectionEnum GetRandomDirection() const
    {
        return static_cast<CharacterDefinitions::DirectionEnum>(rand() % 4 + 1);
    }

    CharacterDefinitions::DirectionEnum FindNextMove(const LevelTerrainMap& levelMap,
                                                     const std::pair<int, int>& src,
                                                     const std::pair<int, int>& dest)
    {
        using namespace CharacterDefinitions;

        std::pair<int, int> move = AStar::FindNextMove(levelMap, std::vector<std::vector<int>>(), {src.second, src.first}, {dest.second, dest.first});

        return GetDirectionToMove(src, move);
    }

    CharacterDefinitions::DirectionEnum FindNextMove(const LevelTerrainMap& levelMap,
                                                     const std::vector<std::vector<int>>& characterMap,
                                                     const std::pair<int, int>& src,
                                                     const std::pair<int, int>& dest)
    {


        std::pair<int, int> move = AStar::FindNextMove(levelMap, characterMap, {src.second, src.first}, {dest.second, dest.first});

        return GetDirectionToMove(src, move);
    }

private:
    Helper()
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }

    ~Helper() {}

    CharacterDefinitions::DirectionEnum GetDirectionToMove(const std::pair<int, int>& src, const std::pair<int, int>& move) const
    {
        using namespace CharacterDefinitions;

        std::pair<int, int> moveFlipped = {move.second, move.first};

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
