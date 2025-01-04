#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
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
    delete gameWindow;
}

void MainWindow::setupStartPage()
{
    startPage = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(startPage);

    QPushButton *startButton = new QPushButton("Start Game", startPage);
    layout->addWidget(startButton);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::showGameWindow);
    stackedWidget->addWidget(startPage);
}

void MainWindow::showGameWindow()
{
    if (gameWindow)
        delete gameWindow;

    gameWindow = new GameWindow("../Assets/map1.csv", new QPixmap("../Assets/tileset.png"), new QPixmap("../Assets/spriteSheet.png"), this);
    connect(gameWindow, &GameWindow::gameOver, this, &MainWindow::showEndPage);

    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);

    gameWindow->setFocus();
}

void MainWindow::setupEndPage(bool isPlayerAlive, int score)
{
    endPage = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(endPage);

    QLabel *resultLabel = new QLabel(isPlayerAlive ? "You Won!" : "You Lost!", endPage);
    QLabel *scoreLabel = new QLabel(QString("Score: %1").arg(score), endPage);
    QPushButton *restartButton = new QPushButton("Restart Game", endPage);

    layout->addWidget(resultLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);

    connect(restartButton, &QPushButton::clicked, this, &MainWindow::resetGame);
    stackedWidget->addWidget(endPage);
}

void MainWindow::showEndPage(bool isPlayerAlive, int score)
{
    setupEndPage(isPlayerAlive, score);
    stackedWidget->setCurrentWidget(endPage);
}

void MainWindow::resetGame()
{
    stackedWidget->setCurrentWidget(startPage);
}
