#ifndef ENDPAGE_H
#define ENDPAGE_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class EndPage : public QWidget
{
    Q_OBJECT

public:
    EndPage(bool isPlayerAlive, int score, QWidget *parent = nullptr);

signals:
    void restartGame();

private:
    void setupLayout(bool isPlayerAlive, int score);
};

#endif // ENDPAGE_H
