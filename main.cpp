#include <QApplication>

#include "MainWindow.h"
#include <QFile>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // QPixmap tileset("../Assets/tileset.png");
    // QPixmap sprites("../Assets/spriteSheet.png");
    // GameWindow window("../Assets/map1.csv", &tileset, &sprites);

    MainWindow w;
    w.show();

    return app.exec();
}
