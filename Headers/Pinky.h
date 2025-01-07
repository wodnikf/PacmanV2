#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"

class Pinky : public Ghost
{
private:
    QPixmap spriteSheet;

public:
    Pinky(Point startPoint, Player *player, QPixmap spriteSheet);

    void loadAnimation() override;

    static Point calculateTarget(const Point &playerPos, const Direction &playerDir, const int &offset);

    void updatePathToTarget(const Pathfinder &pathfinder, Point &targetPos);

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;
};


#endif //PINKY_H
