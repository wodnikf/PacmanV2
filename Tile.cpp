#include "Tile.h"
#include <QPainter>

Tile::Tile(Type type, Point position, int id, QPixmap *tileset) : type(type), position(position), id(id),
                                                                  tileset(tileset)
{}

Type Tile::getType() const
{
    return type;
}

void Tile::setType(Type type)
{
    this->type = type;
}

Point Tile::getPosition() const
{
    return position;
}

int Tile::getId() const
{
    return id;
}

void Tile::setId(int id)
{
    this->id = id;
}

void Tile::render(QPainter &painter) const
{
    const int x = position.x * Globals::TILE_SIZE;
    const int y = position.y * Globals::TILE_SIZE;


    const int tilesPerRow = tileset->width() / (Globals::TILE_SIZE + Globals::MARGIN) + 1;

    const int row = id / tilesPerRow;
    const int col = id % tilesPerRow;

    const int srcX = col * (Globals::TILE_SIZE + Globals::MARGIN);
    const int srcY = row * (Globals::TILE_SIZE + Globals::MARGIN);

    QRect srcRect(srcX, srcY, Globals::TILE_SIZE, Globals::TILE_SIZE);

    painter.drawPixmap(x, y, Globals::TILE_SIZE, Globals::TILE_SIZE, *tileset, srcRect.x(), srcRect.y(),
                       srcRect.width(), srcRect.height());
}

bool Tile::operator==(const Type &typ) const
{
    return type == typ;
}
