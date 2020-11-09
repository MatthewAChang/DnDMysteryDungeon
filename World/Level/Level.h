#ifndef LEVEL_H
#define LEVEL_H

#include "Definitions/TypeDefinitions.h"

#include <map>
#include <memory>
#include <vector>

class Door;
class Enemy;
class Treasure;

class Level
{
public:
    Level(LevelTerrainMap levelTerrainMap,
          LevelInteractableMap levelInteractableMap,
          LevelCharacterMap levelCharacterMap,
          std::map<Location, std::shared_ptr<Treasure>> treasures,
          std::map<Location, std::shared_ptr<Door>> doors,
          std::map<int, std::shared_ptr<Enemy>> enemies);
    ~Level();

    LevelTerrainMap GetLevelTerrainMap() const { return m_levelTerrainMap; }
    MapDefinitions::LevelTerrainMapEnum GetLevelTerrainMapAt(Location location) const;

    LevelInteractableMap GetLevelInteractableMap() const { return m_levelInteractableMap; }
    MapDefinitions::LevelInteractableMapEnum GetLevelInteractableMapAt(Location location) const;

    LevelCharacterMap GetLevelCharacterMap() const { return m_levelCharacterMap; }
    int GetLevelCharacterMapAt(Location location) const;

    void UpdateLevelCharacterMap(Location location, int value) { m_levelCharacterMap[location.second][location.first] = value; }

    std::map<Location, std::shared_ptr<Treasure>> GetTreasures() const { return m_treasures; }
    bool GetTreasure(std::shared_ptr<Treasure>& treasure, Location id);

    std::map<Location, std::shared_ptr<Door>> GetDoors() const { return m_doors; }
    bool GetDoor(std::shared_ptr<Door>& door, Location id);

    std::map<int, std::shared_ptr<Enemy>> GetEnemies() const { return m_enemies; }
    bool GetEnemy(std::shared_ptr<Enemy>& enemy, int id);

private:
    LevelTerrainMap m_levelTerrainMap;
    LevelInteractableMap m_levelInteractableMap;
    LevelCharacterMap m_levelCharacterMap;

    std::map<Location, std::shared_ptr<Treasure>> m_treasures;
    std::map<Location, std::shared_ptr<Door>> m_doors;
    std::map<int, std::shared_ptr<Enemy>> m_enemies;
};

#endif // LEVEL_H
