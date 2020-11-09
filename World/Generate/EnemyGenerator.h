#ifndef ENEMYGENERATOR_H
#define ENEMYGENERATOR_H

#include "Definitions/EnemyDefinitions.h"
#include "Definitions/TypeDefinitions.h"

#include <memory>

class Enemy;
class EquipmentGenerator;

class EnemyGenerator
{
public:
    EnemyGenerator();
    ~EnemyGenerator();

    std::shared_ptr<Enemy> GenerateEnemy(EnemyDefinitions::EnemyEnum eEnemy,
                                         Location location,
                                         CharacterDefinitions::EnemyStateEnum state);

    int GetID() const { return m_NextID; }
    void ResetID() { m_NextID = 1; }

private:
    int CreateHealth(std::pair<int, int> healths);
    void GenerateEquipment(EnemyDefinitions::EnemyEnum eEnemy);

    int m_NextID;
    std::unique_ptr<EquipmentGenerator> m_equipmentGenerator;
};

#endif // ENEMYGENERATOR_H
