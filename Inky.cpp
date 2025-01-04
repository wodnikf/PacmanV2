#include "Inky.h"

#include <iostream>

#include "Blinky.h"

Inky::Inky(Point startPoint, Player *player, QPixmap spriteSheet, Blinky *blinky)
    : Ghost(startPoint, 2), spriteSheet(std::move(spriteSheet)), blinky(blinky)
{
    setPlayer(player);
    Inky::loadAnimation();
}

void Inky::loadAnimation()
{
    const int numberFrames = 2;

    for (int frame = 0; frame < numberFrames; frame++)
    {
        setAnimations(Neutral, Chase, spriteSheet.copy((frame + 5) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                       (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN) * 2,
                                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Frightened,
                      spriteSheet.copy((frame + 7) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       4 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Return, spriteSheet.copy(0, 5 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                        Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
    }
}

void Inky::chase(const Map *map, Pathfinder &pathfinder)
{
    const Point playerPos = snapToGrid(getPlayerPosition());
    const Point blinkyPos = snapToGrid(blinky->getPosition());

    const int offset = 2 * Globals::TILE_SIZE;

    static Point targetMirrorPos = playerPos;
    static bool targetAchieved = false;

    if (targetAchieved)
    {
        targetMirrorPos = playerPos;
        targetAchieved = false;
    }

    switch (getPlayerDirection())
    {
        case UP:
            targetMirrorPos.y -= offset;
            break;
        case DOWN:
            targetMirrorPos.y += offset;
            break;
        case LEFT:
            targetMirrorPos.x -= offset;
            break;
        case RIGHT:
            targetMirrorPos.x += offset;
            break;
        default:
            break;
    }

    Point targetPos = blinkyPos + (targetMirrorPos - blinkyPos);
    targetPos.x = targetPos.x / 2;
    targetPos.y = targetPos.y / 2;


    path = pathfinder.findPath(snapToGrid(position), targetPos, false);
    if (path.empty())
    {
        targetPos = playerPos;
        path = pathfinder.findPath(snapToGrid(position), targetPos, false);
        directions = getDirections(path);
    }
    else
    {
        path = pathfinder.findPath(snapToGrid(position), targetPos, false);
        directions = getDirections(path);
    }


    if (!directions.empty())
    {
        dir = directions.front();
    }
    else
    {
        dir = Neutral;
    }
}

void Inky::scatter(Map *map, Pathfinder &pathfinder)
{
    const Point scatterPos1 = {224, 232};
    const Point scatterPos2 = {160, 192};

    static bool change = false;

    if (position == currentTarget)
    {
        change = !change;
    }
    currentTarget = change ? scatterPos1 : scatterPos2;


    path = pathfinder.findPath(snapToGrid(position), currentTarget, false);

    directions = getDirections(path);

    if (!directions.empty())
    {
        nextDirection = directions.front();
        dir = nextDirection;
    }
}
