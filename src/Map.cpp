#include "../Headers/Map.h"

#include <iostream>
#include <QFile>
#include <QVector>
#include <QXmlStreamReader>

Map::Map(const QString &fileName, const QPixmap *tileset)
{
    this->tileset = *tileset;
    loadMap(fileName);
}

void Map::loadMap(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Failed to open map file:" << fileName;
        return;
    }

    QTextStream in(&file);
    int y = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList tileValues = line.split(",");
        QVector<Tile> row;
        int x = 0;
        for (const QString &tile: tileValues)
        {
            Type tileType;
            if (tile == "93")
            {
                tileType = Pellet;
                numberOfPellets++;
            }
            else if (tile == "95")
            {
                tileType = PowerPellet;
                numberOfPellets++;
            }
            else if (tile == "92")
            {
                tileType = Empty;
            }
            else if (tile == "108")
            {
                tileType = GhostHouse;
            }
            else
            {
                tileType = Wall;
            }

            row.append(Tile(tileType, Point(x, y), tile.toInt(), &this->tileset));

            x++;
        }
        tiles.append(row);
        y++;
    }
    file.close();
}


void Map::render(QPainter &painter)
{
    for (const auto &row: tiles)
    {
        for (const auto &tile: row)
        {
            tile.render(painter);
        }
    }
}


Tile Map::getTile(const Point position) const
{
    const int x = position.x / Globals::TILE_SIZE;
    const int y = position.y / Globals::TILE_SIZE;

    if (y < 0 || y >= tiles.size() || x < 0 || x >= tiles[y].size())
    {
        return Tile(Empty, {x, y}, 92, nullptr);
    }

    return tiles[y][x];
}


int Map::getWidth() const
{
    return tiles.isEmpty() ? 0 : tiles[0].size();
}

int Map::getHeight() const
{
    return tiles.size();
}

void Map::removeTile(Point position)
{
    const int x = position.x / Globals::TILE_SIZE;
    const int y = position.y / Globals::TILE_SIZE;


    tiles[y][x].setType(Empty);
    tiles[y][x].setId(92);
    numberOfPellets--;
}

int Map::getNumberOfPellets() const
{
    return numberOfPellets;
}
