#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void NewLevel();

    // Draw map
    void DrawMap(QPainter* painter);

    Ui::MainWindow *ui;

    std::shared_ptr<GameController> m_pGameController;
};
#endif // MAINWINDOW_H
