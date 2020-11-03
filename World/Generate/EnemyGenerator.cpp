#include "EnemyGenerator.h"

#include "EquipmentGenerator.h"
#include "World/Characters/Enemy.h"
#include "Helper/Helper.h"

#include "assert.h"
#include <time.h>

using namespace EnemyDefinitions;

EnemyGenerator::EnemyGenerator(): m_NextID(1), m_equipmentGenerator(std::make_unique<EquipmentGenerator>())
{
    srand(static_cast<unsigned int>(time(NULL)));
}

EnemyGenerator::~EnemyGenerator()
{
}

std::shared_ptr<Enemy> EnemyGenerator::GenerateEnemy(EnemyEnum eEnemy,
                                                     std::pair<int, int> location,
                                                     CharacterDefinitions::EnemyStateEnum state)
{
    auto enemy = std::make_shared<Enemy>(m_NextID,
                                         ENEMY_NAME[eEnemy],
                                         ENEMY_ABILITY_SCORE[eEnemy],
                                         CreateHealth(ENEMY_HEALTHS[eEnemy]),
                                         m_equipmentGenerator->GenerateArmour(ENEMY_ARMOUR[eEnemy]),
                                         m_equipmentGenerator->GenerateWeapon(ENEMY_WEAPON[eEnemy]),
                                         location,
                                         state);
    ++m_NextID;

    return enemy;
}

int EnemyGenerator::CreateHealth(std::pair<int, int> healths)
{
    return Helper::GetInstance().Roll(healths.first, healths.second);
}
