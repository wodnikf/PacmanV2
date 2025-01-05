#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QStackedWidget>
#include "GameWindow.h"
#include "StartPage.h"
#include "EndPage.h"
#include "DeathAnimationPage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QStackedWidget *stackedWidget;
    StartPage *startPage;
    GameWindow *gameWindow;
    EndPage *endPage;
    DeathAnimationPage *deathAnimationPage;


    void setupStartPage();

public:
    MainWindow(QWidget *parent = nullptr);

    void showGameWindow();

    void handleGameFinished(bool isPlayerAlive, int score);

    void showEndPage(bool isPlayerAlive, int score);

    void showDeathAnimation();

    void resetGame() const;

    void keyPressEvent(QKeyEvent *event) override;

    void setUpFont();

    void setUpBackground();
};

#endif // MAINWINDOW_H
