#include <class/Box.hpp>

Box::Box()
{
    for (auto& bet : bets)
        bet = 0.0f;
}

float Box::getSum()
{
    float temp = 0.0f;
    for (auto& bet : bets)
        temp += bet;
    return temp;
}

std::pair<short, short> Box::getCount()
{
    // If one ace, return two possible values
    // If more than one ace, one or all have to be ones
}

bool Box::addBet(float value)
{
    for (auto& bet : bets)
    {
        if (bet == 0.0f)
        {
            bet = value;
            return true;
        }
    }
    return false;
}
