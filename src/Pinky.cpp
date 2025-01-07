#include "../Headers/Pinky.h"

Pinky::Pinky(Point startPoint, Player *player, QPixmap spriteSheet)
    : Ghost(startPoint, 1), spriteSheet(std::move(spriteSheet))
{
    setPlayer(player);
    Pinky::loadAnimation();
}

void Pinky::loadAnimation()
{
    const int numberFrames = 2;

    for (int frame = 0; frame < numberFrames; frame++)
    {
        setAnimations(Neutral, Chase, spriteSheet.copy((frame + 4) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                       Globals::ANIMATION_TILE_SIZE + Globals::MARGIN,
                                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Frightened,
                      spriteSheet.copy((frame + 7) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       4 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Return, spriteSheet.copy(0, 5 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                        Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
    }
}


Point Pinky::calculateTarget(const Point &playerPos, const Direction &playerDir, const int &offset)
{
    Point targetPos = playerPos;
    switch (playerDir)
    {
        case UP:
            targetPos.y -= offset;
            break;
        case DOWN:
            targetPos.y += offset;
            break;
        case LEFT:
            targetPos.x -= offset;
            break;
        case RIGHT:
            targetPos.x += offset;
            break;
        default:
            break;
    }
    return targetPos;
}

void Pinky::updatePathToTarget(const Pathfinder &pathfinder, Point &targetPos)
{
    path = pathfinder.findPath(snapToGrid(position), targetPos, false);

    if (path.empty())
    {
        targetPos = snapToGrid(getPlayerPosition());
        path = pathfinder.findPath(snapToGrid(position), targetPos, false);
    }

    directions = getDirections(path);
    dir = directions.empty() ? Neutral : directions.front();
}

void Pinky::chase(const Map *map, Pathfinder &pathfinder)
{
    const Point playerPos = snapToGrid(getPlayerPosition());
    const int offset = 6 * Globals::TILE_SIZE;

    static Point targetPos = playerPos;
    static bool targetAchieved = false;

    if (targetAchieved || position == targetPos)
    {
        targetPos = calculateTarget(playerPos, getPlayerDirection(), offset);
        targetAchieved = false;
    }

    updatePathToTarget(pathfinder, targetPos);
}

void Pinky::scatter(Map *map, Pathfinder &pathfinder)
{
    const Point scatterPos1 = {24, 8};
    const Point scatterPos2 = {64, 40};

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
