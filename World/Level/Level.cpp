#include "Level.h"

Level::Level(LevelTerrainMap levelTerrainMap,
             LevelInteractableMap levelInteractableMap,
             LevelCharacterMap levelCharacterMap,
             std::map<Location, std::shared_ptr<Treasure>> treasures,
             std::map<Location, std::shared_ptr<Door>> doors,
             std::map<int, std::shared_ptr<Enemy>> enemies)
    : m_levelTerrainMap(levelTerrainMap),
      m_levelInteractableMap(levelInteractableMap),
      m_levelCharacterMap(levelCharacterMap),
      m_treasures(treasures),
      m_doors(doors),
      m_enemies(enemies)
{

}

Level::~Level()
{
}

MapDefinitions::LevelTerrainMapEnum Level::GetLevelTerrainMapAt(Location location) const
{
    return m_levelTerrainMap[location.second][location.first];
}

MapDefinitions::LevelInteractableMapEnum Level::GetLevelInteractableMapAt(Location location) const
{
    return m_levelInteractableMap[location.second][location.first];
}

int Level::GetLevelCharacterMapAt(Location location) const
{
    return m_levelCharacterMap[location.second][location.first];
}

bool Level::GetTreasure(std::shared_ptr<Treasure>& treasure, Location id)
{
    auto it = m_treasures.find(id);
    if (it != m_treasures.end())
    {
        treasure = it->second;
        return true;
    }

    return false;
}

bool Level::GetDoor(std::shared_ptr<Door> &door, Location id)
{
    auto it = m_doors.find(id);
    if (it != m_doors.end())
    {
        door = it->second;
        return true;
    }

    return false;
}

bool Level::GetEnemy(std::shared_ptr<Enemy>& enemy, int id)
{
    auto it = m_enemies.find(id);
    if (it != m_enemies.end())
    {
        enemy = it->second;
        return true;
    }

    return false;
}
