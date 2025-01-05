#include "../Headers/DeathAnimationPage.h"

#include <QPainter>
#include <QTimer>

DeathAnimationPage::DeathAnimationPage(GameWindow *gameWindow, QWidget *parent)
    : QWidget(parent), currentFrame(0), gameWindow(gameWindow)
{
    loadAnimationFrames();

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, [this]() {
        if (currentFrame < deathAnimation.size())
        {
            update();
            currentFrame++;
        }
        else
        {
            animationTimer->stop();
            emit animationFinished();
        }
    });

    animationTimer->start(500);
}

void DeathAnimationPage::loadAnimationFrames()
{
    QPixmap deathPixmap("../Assets/spriteSheet.png");
    const int numberFrames = 4;

    for (int frame = 0; frame < numberFrames; ++frame)
    {
        deathAnimation.push_back(deathPixmap.copy(
            (frame + 5) * (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN),
            (Globals::ANIMATION_TILE_SIZE + Globals::MARGIN) * 5,
            Globals::ANIMATION_TILE_SIZE, Globals::ANIMATION_TILE_SIZE
        ));
    }
}

void DeathAnimationPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    Point playerPosition = gameWindow->getPlayer()->getPosition();
    const float scaleX = static_cast<float>(width()) / (gameWindow->getMap()->getWidth() * Globals::TILE_SIZE);
    const float scaleY = static_cast<float>(height()) / (gameWindow->getMap()->getHeight() * Globals::TILE_SIZE);

    painter.scale(scaleX, scaleY);

    if (currentFrame < deathAnimation.size())
    {
        painter.drawPixmap(playerPosition.x, playerPosition.y, Globals::TILE_SIZE, Globals::TILE_SIZE,
                           deathAnimation[currentFrame]);
    }
}
