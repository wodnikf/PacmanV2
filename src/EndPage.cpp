#include "../Headers/EndPage.h"
#include <QFontDatabase>


EndPage::EndPage(bool isPlayerAlive, int score, QWidget *parent) : QWidget(parent)
{
    setupLayout(isPlayerAlive, score);
}


void EndPage::setupLayout(bool isPlayerAlive, int score)
{
    auto *layout = new QVBoxLayout(this);

    auto *resultLabel = new QLabel(isPlayerAlive ? "You Won!" : "You Lost!", this);
    auto *scoreLabel = new QLabel(QString("Score: %1").arg(score), this);
    auto *restartButton = new QPushButton("Restart Game", this);

    resultLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(resultLabel);
    layout->addWidget(scoreLabel);
    layout->addWidget(restartButton);

    connect(restartButton, &QPushButton::clicked, this, &EndPage::restartGame);
}
