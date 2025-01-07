#ifndef CLYDE_H
#define CLYDE_H
#include "Ghost.h"
#include <random>


class Clyde : public Ghost
{
private:
    QPixmap spriteSheet;

public:
    Clyde(Point startPoint, Player *player, QPixmap spriteSheet);

    void loadAnimation() override;

    void chase(const Map *map, Pathfinder &pathfinder) override;

    void scatter(Map *map, Pathfinder &pathfinder) override;

    static Point generateRandomTarget(const Map *map, std::mt19937 &rng);

    void updatePathToTarget(const Map *map, const Pathfinder &pathfinder, Point &targetPos);
};


#endif //CLYDE_H
