#include "EndPage.h"

EndPage::EndPage(bool isPlayerAlive, int score, QWidget *parent) : QWidget(parent)
{
    setupLayout(isPlayerAlive, score);
}

void EndPage::setupLayout(bool isPlayerAlive, int score)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *resultLabel = new QLabel(isPlayerAlive ? "You Won!" : "You Lost!", this);
    QLabel *scoreLabel = new QLabel(QString("Score: %1").arg(score), this);
    QPushButton *restartButton = new QPushButton("Restart Game", this);

    layout->addWidget(resultLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);

    connect(restartButton, &QPushButton::clicked, this, &EndPage::restartGame);
}
