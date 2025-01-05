#ifndef GLOBALS_H
#define GLOBALS_H

#include <functional>

namespace Globals {
    const int TILE_SIZE = 8;
    const int ANIMATION_TILE_SIZE = 13;
    const int SPEED = 1;
    const int MARGIN = 1;
}

struct Point
{
    int x, y;

    Point operator+(const Point &other) const
    {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const
    {
        return {x - other.x, y - other.y};
    }

    Point operator+(int tile_size) const
    {
        return {x + tile_size, y + tile_size};
    }

    bool operator==(const Point &point) const
    {
        return x == point.x && y == point.y;
    }
};

struct PointHash
{
    std::size_t operator()(const Point &p) const
    {
        return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
    }
};

enum Type { Wall, Pellet, PowerPellet, Empty, GhostHouse };

enum Direction { UP, DOWN, LEFT, RIGHT, Neutral };

const Point houseExitTarget = {120, 88};
const Point startPos = {120, 112};

inline Point snapToGrid(Point pos)
{
    pos.x = (pos.x / Globals::TILE_SIZE) * Globals::TILE_SIZE;
    pos.y = (pos.y / Globals::TILE_SIZE) * Globals::TILE_SIZE;
    return pos;
}


#endif //GLOBALS_H
