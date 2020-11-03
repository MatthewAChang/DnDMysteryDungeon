#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "World/Characters/Character.h"

#include <atomic>
#include <queue>
#include <memory>
#include <vector>
#include <thread>

class Character;
class Enemy;
class Level;
class LevelGenerator;
class MainWindow;
class Player;

class GameController
{
public:
    GameController(MainWindow* mainWindow);
    ~GameController();

    void NewLevel();
    void EndLevel();

    // Actions
    bool PlayerMove(CharacterDefinitions::DirectionEnum eDirection);
    bool PlayerAttack();
    bool PlayerPotion();
    bool PlayerUse();
    void FinishPlayerTurn() { m_playerTurn = false; }


    std::shared_ptr<Player> GetPlayer() const { return m_pPlayer; }
    std::shared_ptr<Level> GetLevel() const { return m_level; }
    bool IsPlayerTurn() const { return m_playerTurn; }

private:
    bool PlayerAction();
    void EnemyAction(std::shared_ptr<Enemy> enemy);
    bool Move(std::shared_ptr<Character> character, CharacterDefinitions::DirectionEnum eDirection);
    CharacterDefinitions::DirectionEnum IsAdjacent(std::pair<int, int> attackerLocation,
                                                   std::pair<int, int> targetLocation) const;
    void Attack(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target);

    void LevelThread();

    MainWindow* m_mainWindow;

    std::shared_ptr<Player> m_pPlayer;

    std::shared_ptr<Level> m_level;

    std::shared_ptr<LevelGenerator> m_pLevelGenerator;

    std::queue<int> m_characterIDActionQueue;

    std::thread m_levelThread;
    std::atomic<bool> m_levelRunning;

    std::atomic<bool> m_playerTurn;
};

#endif // GAMECONTROLLER_H
