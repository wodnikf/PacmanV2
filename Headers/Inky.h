#ifndef INKY_H
#define INKY_H

#include "Blinky.h"
#include "Ghost.h"

class Inky : public Ghost
{
private:
    QPixmap spriteSheet;
    Blinky *blinky;

public:
    Inky(Point startPoint, Player *player, QPixmap spriteSheet, Blinky *blinky);

    void loadAnimation() override;

    static Point calculateMirrorTarget(const Point &playerPos, const Direction &playerDirection, const int &offset);

    static Point calculateChaseTarget(const Point &blinkyPos, const Point &mirrorTarget);

    void updatePathToTarget(const Pathfinder &pathfinder, Point &targetPos);

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;
};


#endif //INKY_H
