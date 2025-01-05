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

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;
};


#endif //PINKY_H
