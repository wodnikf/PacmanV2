#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include <QWidget>

class EndScreen : public QWidget
{
    Q_OBJECT

public:
    EndScreen(bool playerWon, int score, QWidget *parent = nullptr);

    signals:
        void restartGameClicked();
};

#endif // ENDSCREEN_H
