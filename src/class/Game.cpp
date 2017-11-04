#include <class/Game.hpp>
#include <class/Config.hpp>

#include <fstream>

Game::Game()
{
	used.reserve(32);
    for (auto& box : boxes)
        box = Box();
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

Card Game::Deal()
{
   
    for (auto& box : boxes)
    {
        if (box.getSum() > 0.0f)
        {
			Card copy = deck.back();
			box.addCard(deck.back());
			used.push_back(deck.back());
			deck.pop_back();
        }
    }
}

BetErrorCode Game::addBet(float value, int box)
{
	if (player.balance > value)
	{
		player.balance -= value;
    	if (boxes[box - 1].addBet(value))
			return BetErrorCode::SUCCESS;
		else
			return BetErrorCode::MAX_CAPACITY;
	}
	else 
		return BetErrorCode::INSUFFICIENT_FUNDS;
}
