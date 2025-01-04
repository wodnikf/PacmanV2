#include "StartPage.h"
#include <QVBoxLayout>
#include <QPushButton>

StartPage::StartPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPushButton *startButton = new QPushButton("Start Game", this);

    layout->addWidget(startButton);
    setLayout(layout);

    connect(startButton, &QPushButton::clicked, this, &StartPage::startGameClicked);
}
