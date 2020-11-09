#include "AStarSearchAlgorithm.h"

#include "Definitions/MapDefinitions.h"

#include <queue>

Location AStar::FindNextMove(const LevelTerrainMap& terrainMap,
                             const LevelInteractableMap& interactableMap,
                             const LevelCharacterMap& characterMap,
                             Location src,
                             Location dest)
{
    size_t rowLength = terrainMap.size();
    size_t columnLength = terrainMap[0].size();

    std::vector<std::vector<bool>> closedList (rowLength, std::vector<bool>(columnLength, false));

    std::vector<std::vector<Cell>> cellDetails (rowLength, std::vector<Cell>(columnLength, {-1, -1, FLT_MAX, FLT_MAX, FLT_MAX}));

    int i = src.first;
    int j = src.second;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    cellDetails[i][j].f = 0;
    cellDetails[i][j].g = 0;
    cellDetails[i][j].g = 0;

    std::queue<std::pair<double, Location>> openList;
    openList.push({0.0, {i, j}});

    while (!openList.empty())
    {
        std::pair<double, Location> p = openList.front();

        openList.pop();

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        if (IsDestination(i - 1, j, dest))
        {
            cellDetails[i - 1][j].parent_i = i;
            cellDetails[i - 1][j].parent_j = j;

            return Trace(cellDetails, dest);
        }
        else if (!closedList[i - 1][j] && IsUnblockedMap(terrainMap, interactableMap, characterMap, i - 1, j))
        {
            gNew = cellDetails[i][j].g + 1.0;
            hNew = CalculateHValue(i - 1, j, dest);
            fNew = gNew + hNew;

            if (cellDetails[i - 1][j].f == FLT_MAX || cellDetails[i - 1][j].f > fNew)
            {
                openList.push({fNew, {i - 1, j}});

                // Update the details of this cell
                cellDetails[i - 1][j].f = fNew;
                cellDetails[i - 1][j].g = gNew;
                cellDetails[i - 1][j].h = hNew;
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
            }
        }

        if (IsDestination(i + 1, j, dest))
        {
            cellDetails[i + 1][j].parent_i = i;
            cellDetails[i + 1][j].parent_j = j;

            return Trace(cellDetails, dest);
        }
        else if (!closedList[i + 1][j] && IsUnblockedMap(terrainMap, interactableMap, characterMap, i + 1, j))
        {
            gNew = cellDetails[i][j].g + 1.0;
            hNew = CalculateHValue(i + 1, j, dest);
            fNew = gNew + hNew;

            if (cellDetails[i + 1][j].f == FLT_MAX || cellDetails[i + 1][j].f > fNew)
            {
                openList.push( {fNew, {i + 1, j}});

                // Update the details of this cell
                cellDetails[i + 1][j].f = fNew;
                cellDetails[i + 1][j].g = gNew;
                cellDetails[i + 1][j].h = hNew;
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
            }
        }

        if (IsDestination(i, j + 1, dest))
        {
            cellDetails[i][j + 1].parent_i = i;
            cellDetails[i][j + 1].parent_j = j;

            return Trace(cellDetails, dest);
        }
        else if (!closedList[i][j + 1] && IsUnblockedMap(terrainMap, interactableMap, characterMap, i, j + 1))
        {
            gNew = cellDetails[i][j].g + 1.0;
            hNew = CalculateHValue(i, j + 1, dest);
            fNew = gNew + hNew;

            if (cellDetails[i][j + 1].f == FLT_MAX || cellDetails[i][j + 1].f > fNew)
            {
                openList.push( {fNew, {i, j + 1}});

                // Update the details of this cell
                cellDetails[i][j + 1].f = fNew;
                cellDetails[i][j + 1].g = gNew;
                cellDetails[i][j + 1].h = hNew;
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
            }
        }

        if (IsDestination(i, j - 1, dest))
        {
            cellDetails[i][j - 1].parent_i = i;
            cellDetails[i][j - 1].parent_j = j;

            return Trace(cellDetails, dest);
        }
        else if (!closedList[i][j - 1] && IsUnblockedMap(terrainMap, interactableMap, characterMap, i, j - 1))
        {
            gNew = cellDetails[i][j].g + 1.0;
            hNew = CalculateHValue(i, j - 1, dest);
            fNew = gNew + hNew;

            if (cellDetails[i][j - 1].f == FLT_MAX || cellDetails[i][j - 1].f > fNew)
            {
                openList.push( {fNew, {i, j - 1}});

                // Update the details of this cell
                cellDetails[i][j - 1].f = fNew;
                cellDetails[i][j - 1].g = gNew;
                cellDetails[i][j - 1].h = hNew;
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
            }
        }
    }

    return { -1, -1};
}


bool AStar::IsUnblockedMap(const LevelTerrainMap& terrainMap,
                           const LevelInteractableMap& interactableMap,
                           const LevelCharacterMap& characterMap,
                           int i,
                           int j)
{
    return terrainMap[i][j] == MapDefinitions::eFloor &&
           interactableMap[i][j] == MapDefinitions::eNone &&
            (characterMap.empty() || characterMap[i][j] == MapDefinitions::LEVEL_MAP_EMPTY_ID);
}

double AStar::CalculateHValue(int row, int col, Location dest)
{
    // Return using the distance formula
    return static_cast<double>(sqrt((row - dest.first) * (row - dest.first)
                                    + (col - dest.second) * (col - dest.second)));
}

bool AStar::IsDestination(int row, int col, Location dest)
{
    return row == dest.first && col == dest.second;
}

Location AStar::Trace(const std::vector<std::vector<Cell>>& cellDetails,
                      Location dest)
{
    int prevRow = dest.first;
    int prevCol = dest.second;

    int r = dest.first;
    int c = dest.second;

    while (!(cellDetails[r][c].parent_i == r && cellDetails[r][c].parent_j == c))
    {
        int temp_row = cellDetails[r][c].parent_i;
        int temp_col = cellDetails[r][c].parent_j;
        prevRow = r;
        prevCol = c;
        r = temp_row;
        c = temp_col;
    }

    return {prevRow, prevCol};
}
