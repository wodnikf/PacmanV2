#include "../Headers/Inky.h"
#include "../Headers/Blinky.h"

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

Point Inky::calculateMirrorTarget(const Point &playerPos, const Direction &playerDirection, const int &offset)
{
    Point mirrorTarget = playerPos;

    switch (playerDirection)
    {
        case UP:
            mirrorTarget.y -= offset;
            break;
        case DOWN:
            mirrorTarget.y += offset;
            break;
        case LEFT:
            mirrorTarget.x -= offset;
            break;
        case RIGHT:
            mirrorTarget.x += offset;
            break;
        default:
            break;
    }

    return mirrorTarget;
}

Point Inky::calculateChaseTarget(const Point &blinkyPos, const Point &mirrorTarget)
{
    return {(blinkyPos.x + mirrorTarget.x) / 2, (blinkyPos.y + mirrorTarget.y) / 2};
}

void Inky::updatePathToTarget(const Pathfinder &pathfinder, Point &targetPos)
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

void Inky::chase(const Map *map, Pathfinder &pathfinder)
{
    const Point playerPos = snapToGrid(getPlayerPosition());
    const Point blinkyPos = snapToGrid(blinky->getPosition());
    const int offset = 2 * Globals::TILE_SIZE;

    static Point targetMirrorPos = playerPos;
    static bool targetAchieved = false;

    if (targetAchieved || position == targetMirrorPos)
    {
        targetMirrorPos = calculateMirrorTarget(playerPos, getPlayerDirection(), offset);
        targetAchieved = false;
    }

    Point targetPos = calculateChaseTarget(blinkyPos, targetMirrorPos);
    updatePathToTarget(pathfinder, targetPos);
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
