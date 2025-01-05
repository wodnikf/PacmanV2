#ifndef MAP_H
#define MAP_H

#include "Tile.h"

class Map
{
private:
    QVector<QVector<Tile> > tiles;
    QPixmap tileset;
    int numberOfPellets = 0;

public:
    Map(const QString &fileName, const QPixmap *tileset);

    void loadMap(const QString &fileName);

    void render(QPainter &painter);

    Tile getTile(Point position) const;

    int getNumberOfPellets() const;

    int getWidth() const;

    int getHeight() const;

    void removeTile(Point position);
};


#endif //MAP_H
