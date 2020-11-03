#include "GameController.h"

#include "Definitions/MapDefinitions.h"
#include "Helper/Helper.h"
#include "Interface/MainWindow.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Generate/LevelGenerator.h"
#include "World/Generate/PlayerGenerator.h"
#include "World/Level/Level.h"

#include "assert.h"
#include <map>
#include <chrono>
#include <iostream>

using namespace CharacterDefinitions;

GameController::GameController(MainWindow* mainWindow)
    : m_mainWindow(mainWindow)
    , m_pPlayer(nullptr)
    , m_level(nullptr)
    , m_pLevelGenerator (std::make_shared<LevelGenerator>())
    , m_levelRunning(false)
    , m_playerTurn(false)
{
    auto playerGenerator = std::make_shared<PlayerGenerator>();

    m_pPlayer = playerGenerator->GeneratePlayer("Name", eFighter, eHuman);

    NewLevel();
}

GameController::~GameController()
{
    EndLevel();
}

void GameController::NewLevel()
{
    m_level = m_pLevelGenerator->GenerateLevel(m_pPlayer);

    // Create order of actions for characters
    std::vector<std::pair<std::shared_ptr<Character>, int> > characters;

    characters.push_back({m_pPlayer, Helper::GetInstance().Roll(1, 20) +
                                     Helper::GetInstance().GetAbilityScoreModifier(m_pPlayer->GetAbilityScore(eDexterity))});

    for (const auto& enemy : m_level->GetEnemies())
    {
        characters.push_back({enemy.second, Helper::GetInstance().Roll(1, 20) +
                                            Helper::GetInstance().GetAbilityScoreModifier(enemy.second->GetAbilityScore(eDexterity))});
    }

    std::sort(characters.begin(), characters.end(), [](std::pair<std::shared_ptr<Character>, int>& a, std::pair<std::shared_ptr<Character>, int>& b) {
        return a.second < b.second;
    });

    for (const auto& character : characters)
    {
        m_characterIDActionQueue.push(character.first->GetID());
    }

    m_levelThread = std::thread(&GameController::LevelThread, this);
}

void GameController::LevelThread()
{
    m_levelRunning = true;

    while (m_levelRunning)
    {
        int id = m_characterIDActionQueue.front();
        m_characterIDActionQueue.pop();
        if (id == 0)
        {
            PlayerAction();
        }
        else
        {
            std::shared_ptr<Enemy> enemy = m_level->GetEnemies()[id];
            if (enemy->IsAlive())
            {
                EnemyAction(enemy);
            }
            else
            {
                continue;
            }
        }

        m_characterIDActionQueue.push(id);

        m_mainWindow->update();
    }
}

void GameController::EndLevel()
{
    m_levelRunning = false;
    m_playerTurn = false;

    if (m_levelThread.joinable())
    {
        m_levelThread.join();
    }
}

bool GameController::PlayerAction()
{
    if (m_pPlayer->IsAlive())
    {
        m_playerTurn = true;
        while (m_playerTurn)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return true;
}

void GameController::EnemyAction(std::shared_ptr<Enemy> enemy)
{
    switch(enemy->GetState())
    {
    case eIdle:
        Move(enemy, Helper::GetInstance().GetRandomDirection());
    case eGuard:
        break;
    case eAggro:
    {
        enemy->SetTarget(m_pPlayer);

        std::shared_ptr<Character> target = enemy->GetTarget();
        if (target)
        {
            DirectionEnum direction = IsAdjacent(enemy->GetLocation(), target->GetLocation());
            // Next to target
            if (direction != eNull)
            {
                enemy->SetDirection(direction);
                Attack(enemy, target);
            }
            else
            {
                DirectionEnum direction = Helper::GetInstance().FindNextMove(m_level->GetLevelTerrainMap(),
                                                                             m_level->GetLevelCharacterMap(),
                                                                             enemy->GetLocation(),
                                                                             target->GetLocation());
                if (direction == CharacterDefinitions::eNull)
                {
                    direction = Helper::GetInstance().FindNextMove(m_level->GetLevelTerrainMap(),
                                                                   enemy->GetLocation(),
                                                                   target->GetLocation());
                }

                if (direction != CharacterDefinitions::eNull)
                {
                    Move(enemy, direction);
                }
            }
        }
        break;
    }
    default:
        assert(false);
    }
}

DirectionEnum GameController::IsAdjacent(std::pair<int, int> attackerLocation, std::pair<int, int> targetLocation) const
{
    if (attackerLocation.first - 1 == targetLocation.first && attackerLocation.second == targetLocation.second)
    {
        return eWest;
    }
    if (attackerLocation.first == targetLocation.first && attackerLocation.second - 1 == targetLocation.second)
    {
        return eNorth;
    }
    if (attackerLocation.first + 1 == targetLocation.first && attackerLocation.second == targetLocation.second)
    {
        return eEast;
    }
    if (attackerLocation.first == targetLocation.first && attackerLocation.second + 1 == targetLocation.second)
    {
        return eSouth;
    }

    return eNull;
}

bool GameController::PlayerMove(DirectionEnum eDirection)
{
    return Move(m_pPlayer, eDirection);
}

bool GameController::Move(std::shared_ptr<Character> character, DirectionEnum eDirection)
{
    if (!m_level)
    {
        return false;
    }

    int dx = 0;
    int dy = 0;
    switch(eDirection)
    {
    case eWest:
        dx = -1;
        break;
    case eNorth:
        dy = -1;
        break;
    case eEast:
        dx = 1;
        break;
    case eSouth:
        dy = 1;
        break;
    case eNull:
    default:
        assert(false);
    }

    bool bMoved = false;

    character->SetDirection(eDirection);

    std::pair<int, int> newLocation = { character->GetLocation().first + dx, character->GetLocation().second + dy };
    if (m_level->GetLevelTerrainMap()[newLocation.second][newLocation.first] == MapDefinitions::eFloor)
    {
        if (m_level->GetLevelCharacterMap()[newLocation.second][newLocation.first] == MapDefinitions::eEmpty)
        {
            int valueToMove = m_level->GetLevelCharacterMap()[character->GetLocation().second][character->GetLocation().first];
            m_level->UpdateLevelCharacterMap(character->GetLocation(), MapDefinitions::eEmpty);
            m_level->UpdateLevelCharacterMap(newLocation, valueToMove);
            character->SetLocation(newLocation);

            bMoved = true;
        }
    }

    return bMoved;
}

bool GameController::PlayerAttack()
{
    auto targetLocation = m_pPlayer->GetLocation();

    switch(m_pPlayer->GetDirection())
    {
    case eWest:
        targetLocation.first -= 1;
        break;
    case eNorth:
        targetLocation.second -= 1;
        break;
    case eEast:
        targetLocation.first += 1;
        break;
    case eSouth:
        targetLocation.second += 1;
        break;
    case eNull:
    default:
        assert(false);
    }

    int id = m_level->GetLevelCharacterMap()[targetLocation.second][targetLocation.first];
    if (id != MapDefinitions::eEmpty && id != MapDefinitions::ePlayer)
    {
        std::shared_ptr<Enemy> enemy = m_level->GetEnemies()[id];
        if (enemy->GetLocation() == targetLocation)
        {
            Attack(m_pPlayer, enemy);
        }
    }

    return true;
}

void GameController::Attack(std::shared_ptr<Character> attacker, std::shared_ptr<Character> target)
{
    std::cout << attacker->GetName() << " attacks " << target->GetName() << std::endl;
    int attack = attacker->GetAttack();
    if (attack > target->GetArmourClass())
    {
        int damage = attacker->GetDamage();
        target->TakeDamage(damage);
        if (!target->IsAlive())
        {
            m_level->UpdateLevelCharacterMap(target->GetLocation(), MapDefinitions::eEmpty);
        }
        std::cout << "Deals " << damage << " damage " << std::endl;
    }
}

bool GameController::PlayerPotion()
{
     return false;
}

bool GameController::PlayerUse()
{
     return false;
}
