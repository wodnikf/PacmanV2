#ifndef TILE_H
#define TILE_H

#include <QApplication>
#include "Globals.h"

class Tile
{
private:
    Type type;
    Point position;
    int id;
    QPixmap *tileset;

public:
    Tile(Type type, Point position, int id, QPixmap *tileset);

    Type getType() const;

    void setType(Type type);

    Point getPosition() const;

    int getId() const;

    void setId(int id);

    void render(QPainter &painter) const;

    bool operator==(const Type &typ) const;
};

#endif //TILE_H
