#ifndef TYPEDEFINITIONS_H
#define TYPEDEFINITIONS_H

#include "MapDefinitions.h"

#include <vector>

typedef std::vector<std::vector<MapDefinitions::LevelTerrainMapEnum>> LevelTerrainMap;
typedef std::vector<std::vector<MapDefinitions::LevelInteractableMapEnum>> LevelInteractableMap;
typedef std::vector<std::vector<int>> LevelCharacterMap;
typedef std::pair<int, int> Location;

#endif // TYPEDEFINITIONS_H
