#include "../Headers/StartPage.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

StartPage::StartPage(QWidget *parent) : QWidget(parent)
{
    setupLayout();
}


void StartPage::setupLayout()
{
    auto *layout = new QVBoxLayout(this);

    auto *startButton = new QPushButton("Start Game", this);

    QPixmap image("../Assets/logo.png");
    QImage img = image.toImage().convertToFormat(QImage::Format_ARGB32);

    image = QPixmap::fromImage(img);
    auto *imageLabel = new QLabel(this);
    imageLabel->setPixmap(image);
    imageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(imageLabel);

    layout->addWidget(startButton);
    layout->setAlignment(Qt::AlignCenter);

    connect(startButton, &QPushButton::clicked, this, &StartPage::startGameClicked);
}

