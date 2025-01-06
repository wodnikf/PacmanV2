#include "../Headers/Clyde.h"

#include <iostream>

Clyde::Clyde(Point startPoint, Player *player, QPixmap spriteSheet)
    : Ghost(startPoint, 3), spriteSheet(std::move(spriteSheet))
{
    setPlayer(player);
    Clyde::loadAnimation();
}

void Clyde::loadAnimation()
{
    const int numberFrames = 2;

    for (int frame = 0; frame < numberFrames; frame++)
    {
        setAnimations(Neutral, Chase, spriteSheet.copy((frame + 6) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                       (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN) * 3,
                                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Frightened,
                      spriteSheet.copy((frame + 7) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       4 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Return, spriteSheet.copy(0, 5 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                        Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
    }
}

Point generateRandomPos(const Map *map)
{
    srand(time(nullptr));
    const int X_SIZE = map->getWidth();
    const int Y_SIZE = map->getHeight();
    Point randomTarget;

    do
    {
        const int randomX = rand() % X_SIZE;
        const int randomY = rand() % Y_SIZE;
        randomTarget = {randomX * Globals::TILE_SIZE, randomY * Globals::TILE_SIZE};
    }
    while (map->getTile(randomTarget).getType() == Wall ||
           map->getTile(randomTarget).getType() == GhostHouse);

    return randomTarget;
}


void Clyde::chase(const Map *map, Pathfinder &pathfinder)
{
    static Point targetPos;
    static bool firstTime = true;

    bool targetAchieved = (position == targetPos);

    if (firstTime || targetAchieved)
    {
        targetPos = generateRandomPos(map);
    }

    path = pathfinder.findPath(snapToGrid(position), targetPos, false);

    while (path.empty())
    {
        targetPos = generateRandomPos(map);
        path = pathfinder.findPath(snapToGrid(position), targetPos, false);
    }

    directions = getDirections(path);

    if (!directions.empty())
    {
        dir = directions.front();
    }
    else
    {
        dir = Neutral;
    }

    firstTime = false;
}

void Clyde::scatter(Map *map, Pathfinder &pathfinder)
{
    const Point scatterPos1 = {24, 232};
    const Point scatterPos2 = {64, 192};

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
