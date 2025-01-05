#ifndef PATHFINDER_H
#define PATHFINDER_H
#include "Map.h"

class Pathfinder
{
public:
    Pathfinder(Map *map);

    std::vector<Point> findPath(Point start, Point end, bool insideGhostHouse) const;

    static void printPath(const std::vector<Point> &path);

private:
    Map *map;

    bool isValid(Point position, bool insideGhostHouse) const;


    std::vector<Point> getNeighbors(Point position, bool insideGhostHouse) const;
};


#endif //PATHFINDER_H
