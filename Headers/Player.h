#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Ghost.h"
#include "Score.h"

class Player : public Entity
{
private:
    QPixmap spriteSheet;
    std::vector<QPixmap> animations[4];
    int currentFrame = 0;
    Direction lastDirection = RIGHT;

    std::vector<Ghost *> ghosts;

    Score score;

public:
    Player(Point startPos, QPixmap spriteSheet);

    void render(QPainter &painter) const override;

    void update(Map *map, float deltaTime) override;

    void addGhost(Ghost *ghost);

    void setFrightenedMode() const;

    void loadAnimation();

    void move(Direction newDirection, Map *map);

    void handleKeyPress(Direction newDirection);

    Score *getScore();

    std::vector<Ghost *> getGhosts();

};

#endif // PLAYER_H
