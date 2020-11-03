#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "Controller/GameController.h"
#include "Definitions/MapDefinitions.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Generate/LevelGenerator.h"
#include "World/Generate/PlayerGenerator.h"
#include "World/Level/Level.h"

#include "assert.h"

#include <QGraphicsPixmapItem>

using namespace CharacterDefinitions;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pGameController(std::make_shared<GameController>(this))
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    DrawMap(&painter);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (!m_pGameController->IsPlayerTurn())
    {
        return;
    }

    bool bCompletedAction = false;

    switch(event->key())
    {
    case Qt::Key_Left:
        bCompletedAction = m_pGameController->PlayerMove(eWest);
        break;
    case Qt::Key_Up:
        bCompletedAction = m_pGameController->PlayerMove(eNorth);
        break;
    case Qt::Key_Right:
        bCompletedAction = m_pGameController->PlayerMove(eEast);
        break;
    case Qt::Key_Down:
        bCompletedAction = m_pGameController->PlayerMove(eSouth);
        break;
    case Qt::Key_Z:
        bCompletedAction = m_pGameController->PlayerAttack();
        break;
    case Qt::Key_X:
        bCompletedAction = m_pGameController->PlayerPotion();
        break;
    case Qt::Key_C:
        bCompletedAction = m_pGameController->PlayerUse();
        break;
    }

    update();

    if (bCompletedAction)
    {
        m_pGameController->FinishPlayerTurn();
    }
}

void MainWindow::DrawMap(QPainter* painter)
{
    std::shared_ptr<Player> player = m_pGameController->GetPlayer();
    std::shared_ptr<Level> level = m_pGameController->GetLevel();

    int xOffset = player->GetLocation().first - 6;
    int yOffset = player->GetLocation().second - 3;

    // Draw Map
    for (int i = 0; i < MapDefinitions::MAP_HEIGHT_NUM; ++i)
    {
        for (int j = 0; j < MapDefinitions::MAP_WIDTH_NUM; ++j)
        {
            switch(level->GetLevelTerrainMap()[i + yOffset][j + xOffset])
            {
            case MapDefinitions::eWall:
            {
                QRect rect(j * MapDefinitions::BLOCK_SIZE, i * MapDefinitions::BLOCK_SIZE, MapDefinitions::BLOCK_SIZE, MapDefinitions::BLOCK_SIZE);
                painter->setPen(Qt::SolidLine);
                painter->fillRect(rect, QBrush(Qt::black));
                painter->drawRect(rect);
                break;
            }
            case MapDefinitions::eFloor:
            {
                QRect rect(j * MapDefinitions::BLOCK_SIZE, i * MapDefinitions::BLOCK_SIZE, MapDefinitions::BLOCK_SIZE, MapDefinitions::BLOCK_SIZE);
                painter->setPen(Qt::NoPen);
                painter->fillRect(rect, QBrush(Qt::white));
                painter->drawRect(rect);
                break;
            }
            default:
                assert(false);
            }

            // Draw enemy
            int id = level->GetLevelCharacterMap()[i + yOffset][j + xOffset];
            if (id != MapDefinitions::eEmpty && id != MapDefinitions::ePlayer)
            {
                auto enemy = level->GetEnemies()[id];
                if (enemy->IsAlive())
                {
                    QRect rect(((MapDefinitions::BLOCK_SIZE - 70) / 2) + (j * MapDefinitions::BLOCK_SIZE),
                               ((MapDefinitions::BLOCK_SIZE - 70) / 2) + (i * MapDefinitions::BLOCK_SIZE),
                               70,
                               70);
                    painter->fillRect(rect, QBrush(Qt::blue));
                    painter->drawRect(rect);
                }
            }
        }
    }

    painter->setPen(Qt::SolidLine);

    // Draw Player
    int playerOffsetX = 0;
    int playerOffsetY = 0;
    switch(player->GetDirection())
    {
    case eNorth:
        playerOffsetY -= 5;
        break;
    case eEast:
        playerOffsetX += 5;
        break;
    case eSouth:
        playerOffsetY += 5;
        break;
    case eWest:
        playerOffsetX -= 5;
        break;
    case eNull:
    default:
        assert(false);
    }

    QRect rect(((MapDefinitions::BLOCK_SIZE - 85) / 2) + (6 * MapDefinitions::BLOCK_SIZE) + playerOffsetX,
               ((MapDefinitions::BLOCK_SIZE - 85) / 2) + (3 * MapDefinitions::BLOCK_SIZE) + playerOffsetY,
               85,
               85);
    painter->drawImage(rect, player->GetIdleSprite());


}
