#include "../Headers/MainWindow.h"

#include <QFile>
#include <QFontDatabase>
#include <QKeyEvent>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)), gameWindow(nullptr)
{
    setCentralWidget(stackedWidget);
    setupStartPage();
    stackedWidget->setCurrentWidget(startPage);
    setFixedSize(720, 797);
    setUpFont();
    setUpBackground();
}

void MainWindow::setupStartPage()
{
    startPage = new StartPage(this);
    connect(startPage, &StartPage::startGameClicked, this, &MainWindow::showGameWindow);
    stackedWidget->addWidget(startPage);
}

void MainWindow::showGameWindow()
{
    gameWindow = new GameWindow("../Assets/map1.csv", new QPixmap("../Assets/tileset.png"),
                                new QPixmap("../Assets/spriteSheet.png"), this);

    connect(gameWindow, &GameWindow::gameOver, this, &MainWindow::handleGameFinished);

    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);

    gameWindow->setFocus();
}


void MainWindow::handleGameFinished(bool isPlayerAlive, int score)
{
    if (isPlayerAlive)
    {
        showEndPage(isPlayerAlive, score);
    }
    else
    {
        showDeathAnimation();
    }
}

void MainWindow::showEndPage(bool isPlayerAlive, int score)
{
    endPage = new EndPage(isPlayerAlive, score, this);
    connect(endPage, &EndPage::restartGame, this, &MainWindow::resetGame);

    stackedWidget->addWidget(endPage);
    stackedWidget->setCurrentWidget(endPage);
}

void MainWindow::resetGame() const
{
    stackedWidget->setCurrentWidget(startPage);
}


void MainWindow::showDeathAnimation()
{
    deathAnimationPage = new DeathAnimationPage(gameWindow, this);
    connect(deathAnimationPage, &DeathAnimationPage::animationFinished, [this]() {
        showEndPage(gameWindow->getPlayer()->isAlive(), gameWindow->getPlayer()->getScore()->getScoreAmount());
    });

    stackedWidget->addWidget(deathAnimationPage);
    stackedWidget->setCurrentWidget(deathAnimationPage);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
        {
            QApplication::quit();
        }
        default:
            break;
    }
}


void MainWindow::setUpFont()
{
    const QString fontPath = "../Assets/Font/PressStart2P-Regular.ttf";
    QFile fontFile(fontPath);

    if (!fontFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open font file.";
        return;
    }

    const QByteArray fontData = fontFile.readAll();

    const int fontId = QFontDatabase::addApplicationFontFromData(fontData);

    QStringList families = QFontDatabase::applicationFontFamilies(fontId);
    if (!families.isEmpty())
    {
        QFont customFont(families.first(), 40);
        this->setFont(customFont);
    }
}

void MainWindow::setUpBackground()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::black);
    this->setPalette(palette);
}
