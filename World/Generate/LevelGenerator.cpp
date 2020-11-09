#include "LevelGenerator.h"

#include "Definitions/MapDefinitions.h"
#include "Definitions/TypeDefinitions.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Interactable/Door.h"
#include "World/Interactable/Treasure.h"
#include "World/Item/Key.h"
#include "World/Level/Level.h"
#include "EnemyGenerator.h"

LevelGenerator::LevelGenerator() : m_pEnemyGenerator(std::make_shared<EnemyGenerator>())
{
}

LevelGenerator::~LevelGenerator()
{
}

std::shared_ptr<Level> LevelGenerator::GenerateLevel(std::shared_ptr<Player>& m_pPlayer, int levelNum)
{
    std::shared_ptr<Level> level = nullptr;

    switch(levelNum)
    {
    case 1:
        level = GenerateLevel1(m_pPlayer);
        break;
    default:
        assert(false);
    }

    return level;
}

std::shared_ptr<Level> LevelGenerator::GenerateLevel1(std::shared_ptr<Player>& m_pPlayer)
{
    using namespace MapDefinitions;

    // Level Terrain Map
    std::vector<std::vector<int>> levelTerrainMapTemp = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    LevelTerrainMap levelTerrainMap (levelTerrainMapTemp.size(), std::vector<LevelTerrainMapEnum>(levelTerrainMapTemp[0].size(), eWall));
    for (size_t i = 0; i < levelTerrainMapTemp.size(); ++i)
        for (size_t j = 0; j < levelTerrainMapTemp[0].size(); ++j)
            levelTerrainMap[i][j] = static_cast<LevelTerrainMapEnum>(levelTerrainMapTemp[i][j]);

    // Level Interactable Map
    LevelInteractableMap levelInteractableMap(levelTerrainMap.size(), std::vector<LevelInteractableMapEnum>(levelTerrainMap[0].size(), eNone));
    std::map<Location, std::shared_ptr<Treasure>> treasures;

    std::vector<std::shared_ptr<Item>> items = {std::make_shared<Key>("Boss Key", ItemDefinitions::eBoss)};
    treasures[{10, 13}] = std::make_shared<Treasure>(items, eEast);
    levelInteractableMap[13][10] = eTreasure;

    std::map<Location, std::shared_ptr<Door>> doors;
    doors[{29, 14}] = std::make_shared<Door>(ItemDefinitions::eBoss, eWest);
    levelInteractableMap[14][29] = eDoor;

    // Level Character Map
    LevelCharacterMap levelCharacterMap(levelTerrainMap.size(), std::vector<int>(levelTerrainMap[0].size(), LEVEL_MAP_EMPTY_ID));

    std::map<int, std::shared_ptr<Enemy>> enemies;

    // First room
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {26, 5},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[5][26] = m_pEnemyGenerator->GetID() - 1;

    // Second room
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {26, 15},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[15][26] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {22, 14},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[14][22] = m_pEnemyGenerator->GetID() - 1;

    // Third room
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {15, 14},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[14][15] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {12, 12},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[12][12] = m_pEnemyGenerator->GetID() - 1;

    // Boss room
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {42, 12},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[12][42] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblin,
                                                                           {42, 16},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[16][42] = m_pEnemyGenerator->GetID() - 1;
    enemies[m_pEnemyGenerator->GetID()] = m_pEnemyGenerator->GenerateEnemy(EnemyDefinitions::eGoblinBoss,
                                                                           {42, 14},
                                                                           CharacterDefinitions::eGuard);
    levelCharacterMap[14][42] = m_pEnemyGenerator->GetID() - 1;

    m_pPlayer->SetLocation({8, 5});
    m_pPlayer->SetDirection(eEast);
    levelCharacterMap[5][8] = LEVEL_MAP_PLAYER_ID;

    return std::make_shared<Level>(levelTerrainMap, levelInteractableMap, levelCharacterMap, treasures, doors, enemies);
}
