#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <vector>
#include <memory>

class EnemyGenerator;
class Level;
class Player;

class LevelGenerator
{
public:
    LevelGenerator();
    ~LevelGenerator();

    std::shared_ptr<Level> GenerateLevel(std::shared_ptr<Player>& m_pPlayer, int levelNum);

private:
    std::shared_ptr<Level> GenerateLevel1(std::shared_ptr<Player>& m_pPlayer);

    std::shared_ptr<EnemyGenerator> m_pEnemyGenerator;
};

#endif // LEVELGENERATOR_H
