#ifndef ASTARSEARCHALGORITHM_H
#define ASTARSEARCHALGORITHM_H

#include "Definitions/CharacterDefinitions.h"
#include "Definitions/TypeDefinitions.h"

typedef struct Cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i;
    int parent_j;
    // f = g + h
    double f;
    double g;
    double h;
} Cell;

class AStar
{
public:
    static std::pair<int, int> FindNextMove(const LevelTerrainMap& levelMap,
                                            const std::vector<std::vector<int>>& characterMap,
                                            const std::pair<int, int>& src,
                                            const std::pair<int, int>& dest);

private:
    static bool IsUnblockedLevelMap(const LevelTerrainMap& levelMap, int i, int j);
    static bool IsUnblockedCharacterMap(const std::vector<std::vector<int>>& characterMap, int i, int j);

    static double CalculateHValue(int row, int col, const std::pair<int, int>& dest);
    static bool IsDestination(int row, int col, const std::pair<int, int>& dest);
    static std::pair<int, int> Trace(const std::vector<std::vector<Cell>>& cellDetails,
                                     const std::pair<int, int>& dest);
};

#endif // ASTARSEARCHALGORITHM_H
