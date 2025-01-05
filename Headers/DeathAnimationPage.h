#ifndef DEATHANIMATIONPAGE_H
#define DEATHANIMATIONPAGE_H

#include <QLabel>
#include <QTimer>
#include "GameWindow.h"
#include <QVBoxLayout>

class DeathAnimationPage : public QWidget
{
    Q_OBJECT

public:
    DeathAnimationPage(GameWindow *gameWindow, QWidget *parent = nullptr);

signals:
    void animationFinished();

private:
    QVector<QPixmap> deathAnimation;
    QTimer *animationTimer;
    int currentFrame;
    GameWindow *gameWindow;

    void loadAnimationFrames();

    void paintEvent(QPaintEvent *event) override;
};

#endif // DEATHANIMATIONPAGE_H
