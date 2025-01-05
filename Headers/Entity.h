#ifndef ENTITY_H
#define ENTITY_H

#include <QPainter>
#include <QVector>
#include "Globals.h"
#include "Map.h"
#include "Tile.h"

class Player;
class Ghost;

class Entity
{
protected:
    Point position;
    Direction dir;
    Direction nextDirection;
    bool alive;
    int frameCounter;
    int moveDelay;
    int animationCounter = 0;
    int animationDelay = 5;

public:
    Entity(Point startPos);

    virtual ~Entity() = default;

    Point getPosition() const;

    void setPosition(Point newPosition);

    Direction getDirection() const;

    void setDirection(Direction newDirection);

    void setMoveDelay(int newMoveDelay);

    int getMoveDelay() const;

    bool isAlive() const;

    void setAlive(bool status);

    static QVector<Point> getCorners(Point basePos);

    static Point calculateNewPosition(Point currentPos, Direction direction);

    static bool isValidMove(Point newPos, const Map *map);

    void teleport(Point *position, const Map *map);

    virtual void render(QPainter &painter) const = 0;

    virtual void update(Map *map, float deltaTime) = 0;

    virtual QRect getHitbox() const;
};

#endif // ENTITY_H
