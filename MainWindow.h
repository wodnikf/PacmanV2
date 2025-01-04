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

    ~MainWindow() override;

    void showGameWindow();

    void showEndPage(bool isPlayerAlive, int score);

    void showDeathAnimation();

    void resetGame() const;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
