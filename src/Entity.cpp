#include "../Headers/Entity.h"

Entity::Entity(Point startPos)
    : position(startPos), dir(Neutral), alive(true), frameCounter(0), moveDelay(16),
      nextDirection(Neutral) //16
{}

Point Entity::getPosition() const
{
    return position;
}

void Entity::setPosition(Point newPosition)
{
    position = newPosition;
}

Direction Entity::getDirection() const
{
    return dir;
}

void Entity::setDirection(Direction newDirection)
{
    dir = newDirection;
}

bool Entity::isAlive() const
{
    return alive;
}

void Entity::setAlive(bool status)
{
    alive = status;
}

QVector<Point> Entity::getCorners(Point basePos)
{
    const int sizeMinusOne = Globals::TILE_SIZE - 1;
    return {
        basePos,
        {basePos.x + sizeMinusOne, basePos.y},
        {basePos.x, basePos.y + sizeMinusOne},
        basePos + sizeMinusOne
    };
}


bool Entity::isValidMove(const Point newPos, const Map *map)
{
    QVector<Point> corners = getCorners(newPos);


    for (const Point &corner: corners)
    {
        if (map->getTile(corner).getType() == Wall || map->getTile(corner).getType() == GhostHouse)
        {
            return false;
        }
    }
    return true;
}

void Entity::teleport(Point *position, const Map *map)
{
    const int mapWidthPx = map->getWidth() * Globals::TILE_SIZE;
    if (position->x + Globals::TILE_SIZE <= 16)
    {
        position->x = mapWidthPx - 16;
        nextDirection = LEFT;
    }
    else if (position->x > mapWidthPx - 16 - 1)
    {
        position->x = 16;
        nextDirection = RIGHT;
    }
}

Point Entity::calculateNewPosition(const Point currentPos, const Direction direction)
{
    switch (direction)
    {
        case RIGHT:
            return {currentPos.x + 1, currentPos.y};
        case LEFT:
            return {currentPos.x - 1, currentPos.y};
        case DOWN:
            return {currentPos.x, currentPos.y + 1};
        case UP:
            return {currentPos.x, currentPos.y - 1};
        default:
            return currentPos;
    }
}

void Entity::setMoveDelay(const int newMoveDelay)
{
    moveDelay = newMoveDelay;
}

int Entity::getMoveDelay() const
{
    return moveDelay;
}

QRect Entity::getHitbox() const
{
    const int offset = 3;
    return QRect(position.x + offset, position.y + offset, Globals::TILE_SIZE - offset, Globals::TILE_SIZE - offset);
}
