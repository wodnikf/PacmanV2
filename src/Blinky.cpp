#include "../Headers/Blinky.h"

Blinky::Blinky(Point startPoint, Player *player, QPixmap spriteSheet)
    : Ghost(startPoint, 0), spriteSheet(std::move(spriteSheet))
{
    setPlayer(player);
    Blinky::loadAnimation();
}

void Blinky::loadAnimation()
{
    const int numberFrames = 2;

    for (int frame = 0; frame < numberFrames; frame++)
    {
        setAnimations(Neutral, Chase, spriteSheet.copy((frame + 3) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                       0, Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Frightened,
                      spriteSheet.copy((frame + 7) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       4 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                       Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
        setAnimations(Neutral, Return, spriteSheet.copy(0, 5 * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
                                                        Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE));
    }
}

void Blinky::chase(const Map *map, Pathfinder &pathfinder)
{
    const Point playerPos = snapToGrid(getPlayer()->getPosition());
    currentTarget = playerPos;
    path = pathfinder.findPath(snapToGrid(position), currentTarget, false);
    directions = getDirections(path);
    if (!directions.empty())
    {
        dir = directions.front();
    }
    else
    {
        dir = Neutral;
    }
}

void Blinky::scatter(Map *map, Pathfinder &pathfinder)
{
    Point scatterPos1 = {224, 8};
    Point scatterPos2 = {192, 40};

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
