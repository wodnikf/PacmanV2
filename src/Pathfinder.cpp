#include "../Headers/Pathfinder.h"
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <iostream>

Pathfinder::Pathfinder(Map *map) : map(map)
{}

bool Pathfinder::isValid(const Point position, const bool insideGhostHouse) const
{
    Type tileType = map->getTile(position).getType();
    if (insideGhostHouse && tileType == GhostHouse)
    {
        return true;
    }

    return tileType != Wall && tileType != GhostHouse;
}


std::vector<Point> Pathfinder::findPath(const Point start, const Point end, const bool insideGhostHouse) const
{
    std::queue<Point> frontier;
    std::unordered_map<Point, Point, PointHash> cameFrom;

    frontier.push(start);
    cameFrom[start] = start;
    while (!frontier.empty())
    {
        Point current = frontier.front();
        frontier.pop();

        if (current == end)
        {
            break;
        }
        for (Point next: getNeighbors(current, insideGhostHouse))
        {
            if (isValid(next, insideGhostHouse) && !cameFrom.contains(next))
            {
                frontier.push(next);
                cameFrom[next] = current;
            }
        }
    }

    std::vector<Point> path;
    if (cameFrom.contains(end))
    {
        for (Point at = end; at != start; at = cameFrom[at])
        {
            path.push_back(at);
        }
        path.push_back(start);
        std::ranges::reverse(path);
    }

    return path;
}

std::vector<Point> Pathfinder::getNeighbors(const Point position, const bool insideGhostHouse) const
{
    const std::vector<Point> directions = {
        {0, -Globals::TILE_SIZE}, // Up
        {0, Globals::TILE_SIZE}, // Down
        {-Globals::TILE_SIZE, 0}, // Left
        {Globals::TILE_SIZE, 0} // Right
    };

    std::vector<Point> neighbors;
    for (const Point &dir: directions)
    {
        Point neighbor = position + dir;

        if (neighbor.x < 8)
        {
            neighbor.x += map->getWidth() * Globals::TILE_SIZE - 16;
        }
        else if (neighbor.x > 256 - 16)
        {
            neighbor.x -= map->getWidth() * Globals::TILE_SIZE - 16;
        }

        if (isValid(neighbor, insideGhostHouse))
        {
            neighbors.push_back(neighbor);
        }
    }

    return neighbors;
}

void Pathfinder::printPath(const std::vector<Point> &path)
{
    std::cout << "Path: ";
    for (const Point &p: path)
    {
        std::cout << "(" << p.x << ", " << p.y << ") ";
    }
    std::cout << std::endl;
}
