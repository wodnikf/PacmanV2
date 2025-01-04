#include "StartPage.h"
#include <QPushButton>
#include <QVBoxLayout>

StartPage::StartPage(QWidget *parent) : QWidget(parent)
{
    setupLayout();
}


void StartPage::setupLayout()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *startButton = new QPushButton("Start Game", this);
    layout->addWidget(startButton);

    connect(startButton, &QPushButton::clicked, this, &StartPage::startGameClicked);
}
