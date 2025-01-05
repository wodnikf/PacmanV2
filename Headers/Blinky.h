#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"

class Blinky : public Ghost
{
private:
    QPixmap spriteSheet;

public:
    Blinky(Point startPoint, Player *player, QPixmap spriteSheet);

    void loadAnimation() override;

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;
};

#endif // BLINKY_H
