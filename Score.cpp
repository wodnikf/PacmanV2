#include "Score.h"

Score::Score(): score(0)
{}

int Score::getScoreAmount() const
{
    return score;
}

void Score::incrementScore(const int value)
{
    score += value;
}

std::string Score::toString() const
{
    return std::to_string(score);
}


