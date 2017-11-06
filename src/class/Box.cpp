#include <class/Box.hpp>
#include <fstream>

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
		
Card Box::Top()
{ 
	for (auto& card : cards)
		if (!card.Null())
			return card; 
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

void Box::addCard(Card& card)
{
	std::ofstream file("./log/box");
	file << "addCard() " << card.value;
	for (auto& it : cards)
	{
		if (it.Null())
			it = card;
		break;
	}
}
