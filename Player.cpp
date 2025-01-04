#include "Player.h"
#include <iostream>

Player::Player(Point startPos, QPixmap spriteSheet)
    : Entity(startPos), spriteSheet(std::move(spriteSheet))
{
    loadAnimation();
}

void Player::loadAnimation()
{
    const int numberFrames = 3;
    const int tileSize = Globals::ANIMATION_TILE_SIZE;
    const int margin = Globals::MARGIN;

    for (int frame = 0; frame < numberFrames; ++frame)
    {
        animations[RIGHT].push_back(spriteSheet.copy(frame * (tileSize + margin), 0, tileSize, tileSize));
    }

    auto rotateFrames = [&](const Direction dir, const qreal angle) {
        QTransform rotation;
        rotation.rotate(angle);
        for (const auto &frame: animations[RIGHT])
        {
            animations[dir].push_back(frame.transformed(rotation));
        }
    };

    rotateFrames(LEFT, 180);
    rotateFrames(UP, -90);
    rotateFrames(DOWN, 90);
}

void Player::render(QPainter &painter) const
{
    const int x = position.x;
    const int y = position.y;

    Direction dirToRender;
    if (dir == Neutral)
    {
        dirToRender = lastDirection;
    }
    else
    {
        dirToRender = dir;
    }

    const QPixmap &currentSprite = animations[dirToRender][currentFrame];

    painter.drawPixmap(x, y, Globals::TILE_SIZE, Globals::TILE_SIZE, currentSprite);
}


void Player::update(Map *map, float deltaTime)
{
    const float dtMs = deltaTime * 1000.0f;

    if (nextDirection != Neutral && isValidMove(calculateNewPosition(position, nextDirection), map))
    {
        dir = nextDirection;
        nextDirection = Neutral;
    }

    if (dir != Neutral)
    {
        frameCounter += static_cast<int>(dtMs);

        if (frameCounter >= moveDelay)
        {
            move(dir, map);
            frameCounter -= moveDelay;

            lastDirection = (dir != Neutral) ? dir : lastDirection;

            if ((animationCounter += static_cast<int>(dtMs)) >= animationDelay)
            {
                currentFrame = (currentFrame + 1) % 3;
                animationCounter -= animationDelay;
            }
        }
    }
}


void Player::move(const Direction newDirection, Map *map)
{
    Point newPos = calculateNewPosition(position, newDirection);


    if (isValidMove(newPos, map))
    {
        position = newPos;
    }
    else
    {
        dir = Neutral;
    }

    teleport(&position, map);

    const Point tileCenter = position + Globals::TILE_SIZE / 2;
    const Type tile = map->getTile(tileCenter).getType();

    if (tile == Pellet)
    {
        map->removeTile(tileCenter);

        score.incrementScore(50);
    }
    else if (tile == PowerPellet)
    {
        map->removeTile(tileCenter);
        score.incrementScore(100);
        setFrightenedMode();
    }
}

void Player::handleKeyPress(const Direction newDirection)
{
    nextDirection = newDirection;
}


void Player::addGhost(Ghost *ghost)
{
    if (ghost)
    {
        ghosts.push_back(ghost);
    }
}

void Player::setFrightenedMode() const
{
    for (Ghost *ghost: ghosts)
    {
        if (ghost)
        {
            if (ghost->getGhostMode() == Ghost::House || ghost->getGhostMode() == Ghost::Return)
            {
                continue;
            }
            ghost->setGhostMode(Ghost::Frightened);
            ghost->frightenedTimer = 0;
            ghost->setIsFrightened(true);
        }
    }
}


Score *Player::getScore()
{
    return &score;
}
