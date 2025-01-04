#include "EndScreen.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

EndScreen::EndScreen(bool playerWon, int score, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QString resultMessage = playerWon ? "You Won!" : "Game Over!";
    QLabel *resultLabel = new QLabel(resultMessage, this);
    QLabel *scoreLabel = new QLabel("Score: " + QString::number(score), this);
    QPushButton *restartButton = new QPushButton("Restart Game", this);

    layout->addWidget(resultLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);
    setLayout(layout);

    connect(restartButton, &QPushButton::clicked, this, &EndScreen::restartGameClicked);
}
