#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Definitions/MenuDefinitions.h"

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class GameController;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void keyPressEventGame(QKeyEvent *event);
    void keyPressEventMenu(QKeyEvent *event);
    // Draw map
    void DrawMap(QPainter* painter);

    void setMenuOpen(bool menuOpen);

    Ui::MainWindow *ui;

    std::shared_ptr<GameController> m_pGameController;

    bool m_menuOpen;
    MenuDefinitions::MenuItemEnum m_menuItemSelected;
};
#endif // MAINWINDOW_H
