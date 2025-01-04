#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);

    signals:
        void startGameClicked();
};

#endif // STARTPAGE_H
