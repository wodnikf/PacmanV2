#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include "Player.h"
#include "Pathfinder.h"

class Ghost : public Entity
{
public:
    enum GhostMode { Chase, Scatter, Frightened, House, Return };

private:
    int id;
    Player *player = nullptr;
    bool isFrightened = false;
    GhostMode globalMode = Return;
    bool inHouse = true;
    int currentFrame = 0;
    std::vector<QPixmap> animations[5][5];

    Point startingPoint;

public:
    int scatterTimer = 0;
    const int scatterDuration = 7000;
    int chaseTimer = 0;
    const int chaseDuration = 20000;
    int frightenedTimer = 0;
    const int frightenedDuration = 6000;

    int houseTimer = 0;
    const int houseDuration = 2500 * id;

    Point currentTarget = Point(0, 0);
    std::vector<Point> path;
    std::vector<Direction> directions;

public:
    Ghost(Point startPoint, int id);

    virtual void loadAnimation() = 0;

    virtual void chase(const Map *map, Pathfinder &pathfinder) = 0;

    virtual void scatter(Map *map, Pathfinder &pathfinder) = 0;

    void move(Map *map);

    void update(Map *map, float deltaTime) override;

    void house(const Pathfinder &pathfinder);

    void returnToHouse(const Pathfinder &pathfinder);

    void frightened(Map *map, Pathfinder &pathfinder);

    void setPlayer(Player *player);

    Player *getPlayer() const;

    Point getPlayerPosition() const;

    Direction getPlayerDirection() const;

    void setIsFrightened(bool isFrightened);

    bool getIsFrightened() const;

    int getCurrentFrame() const;

    void setCurrentFrame(int newFrame);

    void setAnimations(int x, int y, const QPixmap &anim);

    bool getInHouse() const;

    void setInHouse(bool isInHouse);

    void respawn();

    GhostMode getGhostMode() const;

    void setGhostMode(GhostMode ghostMode);

    bool collision();

    bool isAtExit() const;

    bool isAtTileCenter() const;

    void printDirections() const;

    static std::vector<Direction> getDirections(const std::vector<Point> &path);

    void render(QPainter &painter) const override;
};

#endif // GHOST_H
