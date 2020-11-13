#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Controller/GameController.h"
#include "Definitions/MapDefinitions.h"
#include "World/Characters/Player.h"
#include "World/Characters/Enemy.h"
#include "World/Generate/LevelGenerator.h"
#include "World/Generate/PlayerGenerator.h"
#include "World/Level/Level.h"
#include "World/Interactable/Door.h"

#include "assert.h"

#include <QGraphicsPixmapItem>

using namespace MapDefinitions;
using namespace MenuDefinitions;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_pGameController(std::make_shared<GameController>(this))
    , m_menuOpen(true)
    , m_menuItemSelected(eStart)
{
    ui->setupUi(this);

    ui->StartLabel->setStyleSheet(SELECTED_FONT);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    if (!m_menuOpen)
    {
        DrawMap(&painter);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_menuOpen)
    {
        keyPressEventMenu(event);
    }
    else
    {
        keyPressEventGame(event);
    }

    update();
}

void MainWindow::keyPressEventMenu(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
    case Qt::Key_Down:
        if (m_menuItemSelected == eStart)
        {
            m_menuItemSelected = eExit;
            ui->StartLabel->setStyleSheet(NOT_SELECTED_FONT);
            ui->ExitLabel->setStyleSheet(SELECTED_FONT);
        }
        else
        {
            m_menuItemSelected = eStart;
            ui->StartLabel->setStyleSheet(SELECTED_FONT);
            ui->ExitLabel->setStyleSheet(NOT_SELECTED_FONT);
        }
        break;
    case Qt::Key_Z:
        if (m_menuItemSelected == eStart)
        {
            setMenuOpen(false);
        }
        else
        {
            close();
        }
        break;
    }
}

void MainWindow::keyPressEventGame(QKeyEvent *event)
{
    if (!m_pGameController->IsPlayerTurn())
    {
        return;
    }

    bool bCompletedAction = false;

    if (event->modifiers() & Qt::ShiftModifier)
    {
        switch(event->key())
        {
        case Qt::Key_Left:
            bCompletedAction = m_pGameController->PlayerTurn(eWest);
            break;
        case Qt::Key_Up:
            bCompletedAction = m_pGameController->PlayerTurn(eNorth);
            break;
        case Qt::Key_Right:
            bCompletedAction = m_pGameController->PlayerTurn(eEast);
            break;
        case Qt::Key_Down:
            bCompletedAction = m_pGameController->PlayerTurn(eSouth);
            break;
        }
    }
    else
    {
        switch(event->key())
        {
        case Qt::Key_Escape:
            setMenuOpen(true);
            break;
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
    }

    if (bCompletedAction)
    {
        m_pGameController->FinishPlayerTurn();
    }
}

void MainWindow::setMenuOpen(bool menuOpen)
{
    m_menuOpen = menuOpen;
    ui->MenuFrame->setVisible(menuOpen);
    if (m_pGameController->GetLevelRunning())
    {
        ui->StartLabel->setText(CONTINUE_TEXT);
    }
    else
    {
        ui->StartLabel->setText(START_TEXT);
    }
}

void MainWindow::DrawMap(QPainter* painter)
{
    using namespace MapDefinitions;

    std::shared_ptr<Player> player = m_pGameController->GetPlayer();
    std::shared_ptr<Level> level = m_pGameController->GetLevel();

    int xOffset = player->GetLocation().first - 6;
    int yOffset = player->GetLocation().second - 3;

    painter->setPen(Qt::NoPen);

    // Draw Map
    for (int i = 0; i < MAP_HEIGHT_NUM; ++i)
    {
        for (int j = 0; j < MAP_WIDTH_NUM; ++j)
        {
            Location locationMap = {j + xOffset, i + yOffset};

            bool visible = !(i == 0 || i == MAP_HEIGHT_NUM - 1 || j == 0 || j == MAP_WIDTH_NUM - 1);
            switch(level->GetLevelTerrainMapAt(locationMap))
            {
            case eWall:
            {
                QRect rect(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                painter->fillRect(rect, Qt::black);
                painter->drawRect(rect);
                break;
            }
            case eFloor:
            {
                QRect rect(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

                painter->fillRect(rect, QBrush(visible ? Qt::white : QColor(100, 100, 100)));
                painter->drawRect(rect);
                break;
            }
            default:
                assert(false);
            }

            // Draw interactables
            switch(level->GetLevelInteractableMapAt(locationMap))
            {
            case eTreasure:
            {
                if (visible)
                {
                    QRect rect(((BLOCK_SIZE - 70) / 2) + (j * BLOCK_SIZE),
                               ((BLOCK_SIZE - 70) / 2) + (i * BLOCK_SIZE),
                               70,
                               70);
                    painter->fillRect(rect, QBrush(Qt::yellow));
                    painter->drawRect(rect);
                }
                break;
            }
            case eDoor:
            {
                std::shared_ptr<Door> door;
                if (level->GetDoor(door, locationMap) && !door->IsOpened())
                {
                    QRect rect(j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
                    painter->fillRect(rect, QBrush(visible ? Qt::blue : Qt::darkBlue));
                    painter->drawRect(rect);
                }
                break;
            }
            case eNone:
            default:
                break;
            }

            if (visible)
            {
                // Draw enemy
                int id = level->GetLevelCharacterMapAt(locationMap);
                std::shared_ptr<Enemy> enemy;
                if (level->GetEnemy(enemy, id))
                {
                    if (enemy->IsAlive())
                    {
                        QRect rect(((BLOCK_SIZE - 70) / 2) + (j * BLOCK_SIZE),
                                   ((BLOCK_SIZE - 70) / 2) + (i * BLOCK_SIZE),
                                   70,
                                   70);
                        painter->fillRect(rect, QBrush(Qt::blue));
                        painter->drawRect(rect);
                    }
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

    QRect rect(((BLOCK_SIZE - 85) / 2) + (6 * BLOCK_SIZE) + playerOffsetX,
               ((BLOCK_SIZE - 85) / 2) + (3 * BLOCK_SIZE) + playerOffsetY,
               85,
               85);
    painter->drawImage(rect, player->GetIdleSprite());


}
