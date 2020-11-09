#include "GameController.h"

#include "Definitions/MapDefinitions.h"
#include "Helper/Helper.h"
#include "Interface/MainWindow.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Generate/LevelGenerator.h"
#include "World/Generate/PlayerGenerator.h"
#include "World/Item/Key.h"
#include "World/Level/Level.h"
#include "World/Interactable/Door.h"
#include "World/Interactable/Treasure.h"

#include "assert.h"
#include <map>
#include <iostream>

using namespace CharacterDefinitions;
using namespace MapDefinitions;

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
    m_level = m_pLevelGenerator->GenerateLevel(m_pPlayer, 1);

    // Create order of actions for characters
    std::vector<std::pair<std::shared_ptr<Character>, int> > characters;

    characters.push_back({m_pPlayer, Helper::GetInstance().Roll(1, 20) +
                                     Helper::GetInstance().GetAbilityScoreModifier(m_pPlayer->GetAbilityScore(eDexterity))});

    for (const auto& enemy : m_level->GetEnemies())
    {
        characters.push_back({enemy.second, Helper::GetInstance().Roll(1, 20) +
                                            Helper::GetInstance().GetAbilityScoreModifier(enemy.second->GetAbilityScore(eDexterity))});
    }

    // Sort by initiative roll
    std::sort(characters.begin(), characters.end(), [](std::pair<std::shared_ptr<Character>, int>& a, std::pair<std::shared_ptr<Character>, int>& b) {
        return a.second < b.second;
    });

    // Place characters into queue by ID
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
        if (id == MapDefinitions::LEVEL_MAP_PLAYER_ID)
        {
            PlayerAction();
        }
        else
        {
            std::shared_ptr<Enemy> enemy;
            if (m_level->GetEnemy(enemy, id) && enemy->IsAlive())
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
        // Check if close enough to player
        if (std::abs(enemy->GetLocation().first - m_pPlayer->GetLocation().first) < 6 &&
            std::abs(enemy->GetLocation().second - m_pPlayer->GetLocation().second) < 3)
        {
            enemy->SetState(eAggro);
            enemy->SetTarget(m_pPlayer);
        }
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
                                                                             m_level->GetLevelInteractableMap(),
                                                                             m_level->GetLevelCharacterMap(),
                                                                             enemy->GetLocation(),
                                                                             target->GetLocation());
                if (direction == MapDefinitions::eNull)
                {
                    direction = Helper::GetInstance().FindNextMove(m_level->GetLevelTerrainMap(),
                                                                   m_level->GetLevelInteractableMap(),
                                                                   enemy->GetLocation(),
                                                                   target->GetLocation());
                }

                if (direction != MapDefinitions::eNull)
                {
                    Move(enemy, direction);
                }
            }
        }
        break;
    }
    case eSleep:
        // Check if next to player
        if (std::abs(enemy->GetLocation().first - m_pPlayer->GetLocation().first) == 1 &&
            std::abs(enemy->GetLocation().second - m_pPlayer->GetLocation().second) == 1)
        {
            enemy->SetState(eAggro);
            enemy->SetTarget(m_pPlayer);
        }
        break;
    default:
        assert(false);
    }
}

DirectionEnum GameController::IsAdjacent(Location attackerLocation, Location targetLocation) const
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

bool GameController::PlayerTurn(DirectionEnum eDirection)
{
    m_pPlayer->SetDirection(eDirection);

    return false;
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

    Location newLocation = { character->GetLocation().first + dx, character->GetLocation().second + dy };
    if (m_level->GetLevelTerrainMapAt(newLocation) == eFloor &&
        (m_level->GetLevelInteractableMapAt(newLocation) == eNone || m_level->GetLevelInteractableMapAt(newLocation) == eDoor) &&
        m_level->GetLevelCharacterMapAt(newLocation) == LEVEL_MAP_EMPTY_ID)
    {
        std::shared_ptr<Door> door;
        if (!m_level->GetDoor(door, newLocation) || (m_level->GetDoor(door, newLocation) && door->IsOpened()))
        {
            int valueToMove = m_level->GetLevelCharacterMapAt(character->GetLocation());
            m_level->UpdateLevelCharacterMap(character->GetLocation(), LEVEL_MAP_EMPTY_ID);
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

    int id = m_level->GetLevelCharacterMapAt(targetLocation);
    std::shared_ptr<Enemy> enemy;
    if (m_level->GetEnemy(enemy, id))
    {
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
            m_level->UpdateLevelCharacterMap(target->GetLocation(), MapDefinitions::LEVEL_MAP_EMPTY_ID);
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

//    MapDefinitions::LevelInteractableMapEnum interactable = m_level->GetLevelInteractableMapAt(targetLocation);

    switch(m_level->GetLevelInteractableMapAt(targetLocation))
    {
    case eTreasure:
    {
        std::shared_ptr<Treasure> treasure;
        if (m_level->GetTreasure(treasure, targetLocation))
        {
            for (const auto& item : treasure->GetItems())
            {
                switch (item->GetItemType())
                {
                case ItemDefinitions::eKey:
                {
                    m_pPlayer->AddKey(std::static_pointer_cast<Key>(item)->GetType());
                    std::cout << "Get Key" << std::endl;
                    break;
                }
                default:
                    break;
                }
            }
            treasure->ClearItems();
        }

        break;
    }
    case eDoor:
    {
        std::shared_ptr<Door> door;
        if (m_level->GetDoor(door, targetLocation))
        {
            if (!door->IsOpened())
            {
                if (m_pPlayer->HasKey(door->GetType()))
                {
                    door->Open();
                    m_pPlayer->UseKey(door->GetType());
                    std::cout << "Use Key" << std::endl;
                }
                else
                {
                    std::cout << "Need Key" << std::endl;
                }
            }
        }
        break;
    }
    default:
        break;
    }
    return false;
}
