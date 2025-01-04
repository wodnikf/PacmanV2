#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "GameWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget *stackedWidget;
    QWidget *startPage;
    GameWindow *gameWindow;
    QWidget *endPage;

    void setupStartPage();
    void setupEndPage(bool isPlayerAlive, int score);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showGameWindow();
    void showEndPage(bool isPlayerAlive, int score);
    void resetGame();
};

#endif // MAINWINDOW_H
