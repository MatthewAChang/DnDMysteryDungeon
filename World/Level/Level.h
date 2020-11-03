#ifndef LEVEL_H
#define LEVEL_H

#include "Definitions/TypeDefinitions.h"

#include <map>
#include <memory>
#include <vector>

class Enemy;

class Level
{
public:
    Level(LevelTerrainMap levelTerrainMap,
          std::vector<std::vector<int>> levelCharacterMap,
          std::map<int, std::shared_ptr<Enemy>> enemies);
    ~Level();

    LevelTerrainMap GetLevelTerrainMap() const { return m_levelTerrainMap; }
    std::vector<std::vector<int>> GetLevelCharacterMap() const { return m_levelCharacterMap; }
    void UpdateLevelCharacterMap(std::pair<int, int> location, int value) { m_levelCharacterMap[location.second][location.first] = value; }
    std::map<int, std::shared_ptr<Enemy>> GetEnemies() const { return m_enemies; }

private:
    LevelTerrainMap m_levelTerrainMap;
    std::vector<std::vector<int>> m_levelCharacterMap;

    std::map<int, std::shared_ptr<Enemy>> m_enemies;
};

#endif // LEVEL_H
