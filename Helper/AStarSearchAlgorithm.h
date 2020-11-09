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
    static Location FindNextMove(const LevelTerrainMap& levelMap,
                                 const LevelInteractableMap& interactableMap,
                                 const LevelCharacterMap& characterMap,
                                 Location src,
                                 Location dest);

private:
    static bool IsUnblockedMap(const LevelTerrainMap& terrainMap,
                               const LevelInteractableMap& interactableMap,
                               const LevelCharacterMap& characterMap,
                               int i,
                               int j);

    static double CalculateHValue(int row, int col, Location dest);
    static bool IsDestination(int row, int col, Location dest);
    static Location Trace(const std::vector<std::vector<Cell>>& cellDetails,
                          Location dest);
};

#endif // ASTARSEARCHALGORITHM_H
