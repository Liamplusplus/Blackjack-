#include <class/BoxManager.hpp>


BoxManager::BoxManager()
{

}
		

void BoxManager::setActive(int index)
{
	current_box = index;
}
		
void BoxManager::Reset();
{
	current_box = 0;
}

Box::BetErrorCode BoxManager::addBet(float value, int box)
{
	if (players[0].getBalance() > value)
	{
		players[0].setBalance(players[0].getBalance() - value);
		if (boxes[box - 1].addBet(value))
			return Box::BetErrorCode::SUCCESS;
		else
			return Box::BetErrorCode::MAX_CAPACITY;
	}
	else 
		return Box::BetErrorCode::INSUFFICIENT_FUNDS;
}

// Increments box
int BoxManager::Next()
{
	if (current_box <= boxes.size() - 1)
		return ++current_box;
	else
	{
		current_box = 0;
		return -1;
	}
}

int BoxManager::nextActiveBox()
{
	for (;current_box < boxes.size(); ++current_box)
	{
		if (!boxes[current_box].inActive())
		{
			return current_box;
		}
	}
	return -1;
}

Box& BoxManager::getActiveBox()
{
	return boxes[current_box];
}

int BoxManager::getActiveIndex()
{
	return current_box;
}

Box& BoxManager::getBox(int index)
{
	return boxes[index];
}
