#include "Level.h"

Level::Level(LevelTerrainMap levelTerrainMap,
             std::vector<std::vector<int>> levelCharacterMap,
             std::map<int, std::shared_ptr<Enemy>> enemies)
    : m_levelTerrainMap(levelTerrainMap),
      m_levelCharacterMap(levelCharacterMap),
      m_enemies(enemies)
{

}

Level::~Level()
{
}
