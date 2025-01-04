#ifndef CLYDE_H
#define CLYDE_H
#include "Ghost.h"


class Clyde : public Ghost
{
private:
    QPixmap spriteSheet;

public:
    Clyde(Point startPoint, Player *player, QPixmap spriteSheet);

    void loadAnimation() override;

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;
};


#endif //CLYDE_H
