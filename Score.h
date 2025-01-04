#ifndef SCORE_H
#define SCORE_H
#include <string>


class Score
{
private:
    int score;

public:
    Score();

    int getScoreAmount() const;
    void incrementScore(int value);

    std::string toString() const;
};



#endif //SCORE_H
