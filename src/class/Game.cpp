#include <class/Game.hpp>
#include <class/Config.hpp>

#include <fstream>

Game::Game()
{
	used.reserve(32);
    for (auto& box : boxes)
        box = Box();

    deck.Shuffle();
}

void Game::Run()
{
    /* 
     * Choose bet (Enter amount (or quit))
     * Play hand  (Hit or sit)
     * Deal dealers hand
     * Repeat
     */

}

void Game::Deal()
{
   
    for (auto& box : boxes)
    {
        if (box.getSum() > 0.0f)
        {
			Card top = deck.Top();
			box.addCard(top);
			used.push_back(top);
			deck.Pop();
        }
    }
}

Game::BetErrorCode Game::addBet(float value, int box)
{
	if (players[0].balance > value)
	{
		players[0].balance -= value;
    	if (boxes[box - 1].addBet(value))
			return BetErrorCode::SUCCESS;
		else
			return BetErrorCode::MAX_CAPACITY;
	}
	else 
		return BetErrorCode::INSUFFICIENT_FUNDS;
}
