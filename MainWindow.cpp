#include "MainWindow.h"
#include <iostream>
#include <QKeyEvent>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)), gameWindow(nullptr)
{
    setCentralWidget(stackedWidget);
    setupStartPage();
    stackedWidget->setCurrentWidget(startPage);
    setFixedSize(720, 797);
}

MainWindow::~MainWindow()
{
    delete startPage;
    delete gameWindow;
    delete endPage;
    delete deathAnimationPage;
    delete stackedWidget;
}

void MainWindow::setupStartPage()
{
    startPage = new StartPage(this);
    connect(startPage, &StartPage::startGameClicked, this, &MainWindow::showGameWindow);
    stackedWidget->addWidget(startPage);
}

void MainWindow::showGameWindow()
{
    if (gameWindow)
        delete gameWindow;

    gameWindow = new GameWindow("../Assets/map1.csv", new QPixmap("../Assets/tileset.png"),
                                new QPixmap("../Assets/spriteSheet.png"), this);
    connect(gameWindow, &GameWindow::gameOver, this, &MainWindow::showDeathAnimation);

    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);

    gameWindow->setFocus();
}


void MainWindow::showEndPage(bool isPlayerAlive, int score)
{
    EndPage *endPage = new EndPage(isPlayerAlive, score, this);
    connect(endPage, &EndPage::restartGame, this, &MainWindow::resetGame);

    stackedWidget->addWidget(endPage);
    stackedWidget->setCurrentWidget(endPage);
}

void MainWindow::resetGame() const
{
    stackedWidget->setCurrentWidget(startPage);
}


void MainWindow::showDeathAnimation()
{
    DeathAnimationPage *deathAnimationPage = new DeathAnimationPage(gameWindow, this);
    connect(deathAnimationPage, &DeathAnimationPage::animationFinished, [this]() {
        showEndPage(false, gameWindow->getPlayer()->getScore()->getScoreAmount());
    });

    stackedWidget->addWidget(deathAnimationPage);
    stackedWidget->setCurrentWidget(deathAnimationPage);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
        {
            exit(0);
        }
        default:
            break;
    }
}
