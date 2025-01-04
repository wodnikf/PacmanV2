#include "GameWindow.h"

#include <QPainter>
#include <QKeyEvent>
#include "Clyde.h"
#include "Inky.h"

GameWindow::GameWindow(const QString &mapFile, QPixmap *tileset, const QPixmap *sprites, QWidget *parent)
    : QWidget(parent)
{
    timer.start();
    lastTime = timer.elapsed();

    gameMap = new Map(mapFile, tileset);
    player = new Player(Point{124, 184}, *sprites);
    blinky = new Blinky(Point{112, 112}, player, *sprites);
    pinky = new Pinky(Point{112, 112}, player, *sprites);
    inky = new Inky(Point{112, 112}, player, *sprites, blinky);
    clyde = new Clyde(Point{112, 112}, player, *sprites);
    player->addGhost(blinky);
    player->addGhost(pinky);
    player->addGhost(inky);
    player->addGhost(clyde);
}


GameWindow::~GameWindow()
{
    delete gameMap;
    delete player;
    delete blinky;
    delete pinky;
    delete inky;
    delete clyde;
}

void GameWindow::updateGame()
{
    const qint64 currentTime = timer.elapsed();
    const float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    player->update(gameMap, deltaTime);
    blinky->update(gameMap, deltaTime);
    pinky->update(gameMap, deltaTime);
    inky->update(gameMap, deltaTime);
    clyde->update(gameMap, deltaTime);

    if (!player->isAlive() || gameMap->getNumberOfPellets() == 0)
    {
        emit gameOver(player->isAlive(), player->getScore()->getScoreAmount());
    }

    update();
}

void GameWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    const float scaleX = static_cast<float>(width()) / (gameMap->getWidth() * Globals::TILE_SIZE);
    const float scaleY = static_cast<float>(height()) / (gameMap->getHeight() * Globals::TILE_SIZE);

    painter.scale(scaleX, scaleY);

    updateGame();
    gameMap->render(painter);
    player->render(painter);
    blinky->render(painter);
    pinky->render(painter);
    inky->render(painter);
    clyde->render(painter);

    update();
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    Direction newDirection = Neutral;

    switch (event->key())
    {
        case Qt::Key_Up:
            newDirection = UP;
            break;
        case Qt::Key_Down:
            newDirection = DOWN;
            break;
        case Qt::Key_Left:
            newDirection = LEFT;
            break;
        case Qt::Key_Right:
            newDirection = RIGHT;
            break;
        case Qt::Key_1:
            player->setMoveDelay(player->getMoveDelay() - 1);
            break; //to fun to remove this

        //DEBUG
        case Qt::Key_2:
            player->setAlive(false);
            break;
        case Qt::Key_3:
            clyde->setGhostMode(Ghost::Return);
            break;
        case Qt::Key_4:
            blinky->setMoveDelay(blinky->getMoveDelay() - 1);
            break;
        case Qt::Key_Escape:
            exit(0);

        default:
            break;
    }

    if (newDirection != Neutral)
    {
        player->handleKeyPress(newDirection);
    }
}

Map *GameWindow::getMap() const
{
    return gameMap;
}

Player *GameWindow::getPlayer() const
{
    return player;
}