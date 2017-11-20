#include <class/Box.hpp>
#include <fstream>
#include <algorithm>

Box::Box() : status(Box::Status::UNDER), active(false)
{
    for (auto& bet : bets)
        bet = 0.0f;

    for (auto& card : cards)
        card = Card();
}

float Box::getSum()
{
    float temp = 0.0f;
    for (auto& bet : bets)
        temp += bet;
    return temp;
}

// Two possible values
// Every ace is a one || One ace is an 11
// getCount().first being the safest and
// getCount().second being the highest
std::pair<short, short> Box::getCount()
{
	std::pair<short, short> count = {0, 0};
	bool counted_eleven = false;
	for (auto& card : cards)
	{
		if (card.value >= 10)
		{
			count.first += 10;
			count.second += 10;
		}
		else if (card.value == 1) // Ace
		{
			count.first += 1;
			if (!counted_eleven)
			{
				count.second += 11;
				counted_eleven = true;
			}
			else
				count.second += 1;
		}
		else
		{
			count.first += card.value;
			count.second += card.value;
		}
	}

	if (count.second > 21 || count.first == count.second)
		count.second = -1;

	return count;

}

short Box::Highest()
{
    std::pair<short, short> count = getCount();
    if (count.second == -1)
        return count.first;
    else
        return count.second;
}

// No cards
bool Box::Empty() 				
{ 
	return cards[0].Null(); 
}

// No bets
bool Box::inActive()
{
	return getSum() == 0; 
}

// Busted
bool Box::Bust()
{
	return getCount().first > 21;
}

bool Box::Blackjack()
{
	std::pair<short, short> count = getCount();
	return (getCount().first == 21 || getCount().second == 21);
}

Card Box::Bottom()
{ 
	for (auto& card : cards)
		if (!card.Null())
			return card; 
	return Card();
}

Card Box::Top()
{
	for (std::array<Card, 5>::reverse_iterator rit = cards.rbegin(); rit != cards.rend(); ++rit)
		if (!rit->Null())
			return *rit;
	return Card();
}

int Box::nCards()
{
	return std::count_if(cards.begin(), cards.end(), [](Card& c) { return !c.Null(); });
}

bool Box::addBet(float value)
{
    active = true;
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
	for (auto& it : cards)
		if (it.Null())
		{
			it = card;
			break;
		}
	setStatus();
}

void Box::setStatus()
{
	std::pair<short, short> count = getCount();

	if (count.first > 21)
    {
		status = Status::BUST;
        active = false;
    }
	else if (count.second == 21 || count.first == 21)
    {
        if (nCards() == 2)
        {
			status = Status::BLACKJACK;
            active = false;
        }
        else
			status = Status::TWENTY_ONE;
    }
	else if (nCards() == 5)
    {
		status = Status::FULL;
        active = false;
    }
	else
		status = Status::UNDER;	
}

void Box::Pay(float factor)
{
    
}

bool Box::Active()
{
    return active;
}

void Box::setActive(bool b)
{
    active = b;
}

Box::Status Box::getStatus()
{
	return status;
}

void Box::write_form(std::ostream& stream)
{
	bool active = !inActive();
	stream << "<Active> " << std::boolalpha << active;
	stream << "<Busted> " << std::boolalpha << Bust();
	if (active)
	{
		stream << "\n<Bets> ";
		for (auto& bet : bets)
			stream << bet << " ";
		stream << "\n<Cards> " << nCards() << std::endl;
		for (auto& card : cards)
		{
			card.write_form(stream);
			stream << '\n';
		}
		std::pair<short, short> count = getCount();
		stream << "<Count> " << count.first << ", " << count.second << std::endl;
	}
}
