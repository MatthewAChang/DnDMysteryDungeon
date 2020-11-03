#include "LevelGenerator.h"

#include "Definitions/MapDefinitions.h"
#include "Definitions/TypeDefinitions.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Level/Level.h"
#include "EnemyGenerator.h"

#include <chrono>
#include <thread>

LevelGenerator::LevelGenerator() : m_pEnemyGenerator(std::make_shared<EnemyGenerator>())
{
}

LevelGenerator::~LevelGenerator()
{
}

std::shared_ptr<Level> LevelGenerator::GenerateLevel(std::shared_ptr<Player>& m_pPlayer)
{
    using namespace MapDefinitions;

    std::vector<std::vector<int>> levelTerrainMapTemp = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    LevelTerrainMap levelTerrainMap (levelTerrainMapTemp.size(), std::vector<LevelTerrainMapEnum>(levelTerrainMapTemp[0].size(), eWall));
    for (size_t i = 0; i < levelTerrainMapTemp.size(); ++i)
        for (size_t j = 0; j < levelTerrainMapTemp[0].size(); ++j)
            levelTerrainMap[i][j] = static_cast<LevelTerrainMapEnum>(levelTerrainMapTemp[i][j]);

    std::vector<std::vector<int>> levelCharacterMap(levelTerrainMap.size(), std::vector<int>(levelTerrainMap[0].size(), MapDefinitions::eEmpty));

    std::map<int, std::shared_ptr<Enemy>> enemies;

    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {7, 7},
                                                                           CharacterDefinitions::eAggro);
    levelCharacterMap[7][7] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {19, 4},
                                                                           CharacterDefinitions::eAggro);
    levelCharacterMap[4][19] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {6, 12},
                                                                           CharacterDefinitions::eAggro);
    levelCharacterMap[12][6] = m_pEnemyGenerator->GetID() - 1;

    m_pPlayer->SetLocation({6, 3});
    levelCharacterMap[3][6] = MapDefinitions::ePlayer;

    return std::make_shared<Level>(levelTerrainMap, levelCharacterMap, enemies);
}
