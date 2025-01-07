#include "../Headers/Clyde.h"

Clyde::Clyde(const Point startPoint, Player *player, QPixmap spriteSheet)
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

Point Clyde::generateRandomTarget(const Map *map, std::mt19937 &rng)
{
    std::uniform_int_distribution<int> xDist(0, map->getWidth() - 1);
    std::uniform_int_distribution<int> yDist(0, map->getHeight() - 1);

    Point randomTarget;
    do
    {
        const int randomX = xDist(rng);
        const int randomY = yDist(rng);
        randomTarget = {randomX * Globals::TILE_SIZE, randomY * Globals::TILE_SIZE};
    }
    while (map->getTile(randomTarget).getType() == Wall || map->getTile(randomTarget).getType() == GhostHouse);

    return randomTarget;
}

void Clyde::updatePathToTarget(const Map *map, const Pathfinder &pathfinder, Point &targetPos)
{
    path = pathfinder.findPath(snapToGrid(position), targetPos, false);

    while (path.empty())
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        targetPos = generateRandomTarget(map, rng);
        path = pathfinder.findPath(snapToGrid(position), targetPos, false);
    }

    directions = getDirections(path);
    dir = directions.empty() ? Neutral : directions.front();
}

void Clyde::chase(const Map *map, Pathfinder &pathfinder)
{
    static Point targetPos;
    static bool firstTime = true;

    bool targetAchieved = (position == targetPos);

    if (firstTime || targetAchieved)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        targetPos = generateRandomTarget(map, rng);
    }

    updatePathToTarget(map, pathfinder, targetPos);

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
