#include "Ghost.h"
#include <iostream>

Ghost::Ghost(Point startPoint, int id)
    : Entity(startPoint), id(id)
{}

void Ghost::setPlayer(Player *player)
{
    this->player = player;
}

Player *Ghost::getPlayer() const
{
    return player;
}

Point Ghost::getPlayerPosition() const
{
    return player ? player->getPosition() : Point{-1, -1};
}

Direction Ghost::getPlayerDirection() const
{
    return player ? player->getDirection() : Neutral;
}

bool Ghost::getIsFrightened() const
{
    return isFrightened;
}

void Ghost::setIsFrightened(bool isFrightened)
{
    this->isFrightened = isFrightened;
}

bool Ghost::getInHouse() const
{
    return inHouse;
}

void Ghost::setInHouse(bool isInHouse)
{
    inHouse = isInHouse;
}

Ghost::GhostMode Ghost::getGhostMode() const
{
    return globalMode;
}

void Ghost::setGhostMode(GhostMode ghostMode)
{
    globalMode = ghostMode;
}

void Ghost::respawn()
{
    setMoveDelay(16);
    setAlive(true);
    setIsFrightened(false);
    frightenedTimer = 0;
}

bool Ghost::collision()
{
    if (player)
    {
        const QRect playerHitbox = player->getHitbox();
        QRect ghostHitbox = getHitbox();

        if (playerHitbox.intersects(ghostHitbox))
        {
            if (getIsFrightened())
            {
                setIsFrightened(false);
                setGhostMode(Return);
                setAlive(false);
                getPlayer()->getScore()->incrementScore(200 * (id +1));
                return true;
            }
            if (isAlive())
            {
                dir = Neutral;
                getPlayer()->setAlive(false);
                return true;
            }
        }
    }
    return false;
}

bool Ghost::isAtExit() const
{
    return snapToGrid(position) == houseExitTarget;
}

bool Ghost::isAtTileCenter() const
{
    return (position.x % Globals::TILE_SIZE == 0 && position.y % Globals::TILE_SIZE == 0);
}

void Ghost::printDirections() const
{
    std::cout << "Directions: ";
    for (const auto direction: directions)
    {
        std::cout << direction << " ";
    }
    std::cout << std::endl;
}

std::vector<Direction> Ghost::getDirections(const std::vector<Point> &path)
{
    std::vector<Direction> directions;
    Point previousPoint = path.front();

    for (size_t i = 1; i < path.size(); ++i)
    {
        Point currentPoint = path[i];
        if (currentPoint.x > previousPoint.x)
            directions.push_back(RIGHT);
        else if (currentPoint.x < previousPoint.x)
            directions.push_back(LEFT);
        else if (currentPoint.y > previousPoint.y)
            directions.push_back(DOWN);
        else if (currentPoint.y < previousPoint.y)
            directions.push_back(UP);

        previousPoint = currentPoint;
    }
    return directions;
}

void Ghost::move(Map *map)
{
    if (!getPlayer())
        return;

    collision();

    Pathfinder pathfinder(map);

    if (isAtTileCenter())
    {
        switch (getGhostMode())
        {
            case Chase:
                chase(map, pathfinder);
                break;
            case Scatter:
                scatter(map, pathfinder);
                break;
            case Frightened:
                frightened(map, pathfinder);
                break;
            case House:
                house(pathfinder);
                break;
            case Return:
                returnToHouse(pathfinder);
                break;
            default:
                break;
        }
    }

    if (dir != Neutral)
    {
        position = calculateNewPosition(position, dir);
        teleport(&position, map);
    }
}

void Ghost::house(const Pathfinder &pathfinder)
{
    if (isAtExit())
    {
        setGhostMode(Chase);
        return;
    }
    currentTarget = houseExitTarget;
    path = pathfinder.findPath(snapToGrid(position), currentTarget, true);
    directions = getDirections(path);
    if (!directions.empty())
    {
        dir = directions.front();
    }
}

void Ghost::returnToHouse(const Pathfinder &pathfinder)
{
    const Point startPosition1 = {120, 112};
    const Point startPosition2 = {136, 112};

    if (getInHouse())
    {
        setMoveDelay(16);
    }
    else
    {
        setMoveDelay(-5);
    }

    static bool change = false;

    if (position == currentTarget)
    {
        change = !change;
    }
    currentTarget = change ? startPosition1 : startPosition2;

    path = pathfinder.findPath(snapToGrid(position), currentTarget, true);
    directions = getDirections(path);
    if (!directions.empty())
    {
        dir = directions.front();
    }
}

void Ghost::frightened(Map *map, Pathfinder &pathfinder)
{
    setMoveDelay(21);
    scatter(map, pathfinder);
}


void Ghost::update(Map *map, const float deltaTime)
{
    const float dtMs = deltaTime * 1000.0f;

    frameCounter += static_cast<int>(dtMs);

    if (frameCounter >= moveDelay + 10)
    {
        move(map);
        frameCounter -= moveDelay + 10;
    }

    if (getGhostMode() == Scatter)
    {
        scatterTimer += static_cast<int>(dtMs);
        if (scatterTimer >= scatterDuration)
        {
            setGhostMode(Chase);
            scatterTimer = 0;
        }
    }

    if (getGhostMode() == Chase)
    {
        chaseTimer += static_cast<int>(dtMs);
        if (chaseTimer >= chaseDuration)
        {
            setGhostMode(Scatter);
            chaseTimer = 0;
        }
    }


    if (position == houseExitTarget && getGhostMode() == House)
    {
        setInHouse(false);
        setGhostMode(Scatter);
        snapToGrid(position);
    }

    if (getInHouse())
    {
        houseTimer += static_cast<int>(dtMs);
        if (houseTimer >= houseDuration)
        {
            respawn();
            setGhostMode(House);
            houseTimer = 0;
        }
    }

    if (position == startPos)
    {
        setInHouse(true);
    }

    if (getIsFrightened())
    {
        scatterTimer = 0;
        chaseTimer = 0;
        frightenedTimer += static_cast<int>(dtMs);

        if (frightenedTimer >= frightenedDuration)
        {
            setMoveDelay(16);
            setIsFrightened(false);
            setGhostMode(Chase);
            frightenedTimer = 0;
        }
    }

    animationCounter += static_cast<int>(dtMs);


    if (animationCounter >= animationDelay * 20)
    {
        setCurrentFrame((getCurrentFrame() + 1) % 2);
        animationCounter = 0;
    }
}


void Ghost::render(QPainter &painter) const
{
    const int x = position.x;
    const int y = position.y;

    QPixmap currentSprite;
    if (getIsFrightened())
    {
        currentSprite = animations[Neutral][Frightened][getCurrentFrame()];
    }
    else if (getInHouse())
    {
        currentSprite = animations[Neutral][Chase][getCurrentFrame()];
    }
    else if (getGhostMode() == Return)
    {
        currentSprite = animations[Neutral][Return][getCurrentFrame()];
    }
    else
    {
        currentSprite = animations[Neutral][Chase][getCurrentFrame()];
    }


    painter.drawPixmap(x, y, Globals::TILE_SIZE, Globals::TILE_SIZE, currentSprite);
}

int Ghost::getCurrentFrame() const
{
    return currentFrame;
}

void Ghost::setCurrentFrame(const int newFrame)
{
    currentFrame = newFrame;
}


void Ghost::setAnimations(const int x, const int y, const QPixmap &anim)
{
    animations[x][y].push_back(anim);
}
