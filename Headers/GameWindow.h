#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include "Blinky.h"
#include "Clyde.h"
#include "Inky.h"
#include "Map.h"
#include "Pinky.h"
#include "Player.h"

class GameWindow final : public QWidget
{
    Q_OBJECT

private:
    QElapsedTimer timer;
    qint64 lastTime = 0;
    Map *gameMap;
    Player *player;
    Blinky *blinky;
    Pinky *pinky;
    Inky *inky;
    Clyde *clyde;

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

public:
    GameWindow(const QString &mapFile, const QPixmap *tileset, const QPixmap *sprites, QWidget *parent = nullptr);

    ~GameWindow() override;

    void updateGame();

    Map *getMap() const;

    Player *getPlayer() const;

    signals:
        void gameOver(bool isPlayerAlive, int score);

};

#endif // GAMEWINDOW_H
