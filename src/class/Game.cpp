#include <class/Game.hpp>
#include <class/Config.hpp>

#include <fstream>
#include <algorithm>

Game::Game() : current_player(0), current_box(0), active(false)
{
	initial_state = InitialState::FIRST_ROUND;
	used.reserve(32);
    for (auto& box : boxes)
        box = Box();

    deck.Shuffle(rand_gen);
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

/* Deals to all boxes, does not allow player to interupt
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
*/

// Interuptable initial deal phase
// Find active box from 0 - 5
// If none return error
// if current_box == 5
int Game::InitialDeal()
{
	int active_box = nextActiveBox();
	nextBox();

	if (active_box != -1)
	{
		active = true;
		Card top = deck.Top();
		boxes[active_box].addCard(top);
		used.push_back(top);
		deck.Pop();
		return active_box;
	}
	else
	{
		if (!active)
		{
			current_box = 0;
			return -1; // No bets have been placed
		}
		else if (initial_state == InitialState::FIRST_ROUND)
		{
			Card top = deck.Top();
			dealer.addCard(top);
			used.push_back(top);
			deck.Pop();
			initial_state = InitialState::SECOND_ROUND;
			return -2;
		}
		else
			return -3;
	}
	if (nextActiveBox() == -1 && initial_state == InitialState::SECOND_ROUND)
		return -3;
}



void Game::logState()
{
	std::ofstream stream("./log/game_state", std::ios_base::out);
	stream << "<Gamestate>\n";

	stream << "<CurrentPlayer> " << current_player;
	stream << "\n<CurrentBox> " << current_box;
	stream << "\n\n<Boxes>\n\n"; 

	for (auto& box : boxes)
	{
		box.write_form(stream);
		stream << '\n';
	}
	stream << "<Dealer>\n";
	dealer.write_form(stream);
	stream << '\n';

	stream << "\n\n<Players>\n\n"; 
	for (auto& player : players)
	{
		player.write_form(stream);
		stream << '\n';
	}
}

// Go to next active box, if active add card
int Game::Hit()
{
	if (current_box < boxes.size())
	{
		Box& box = boxes[current_box];
		box.addCard(deck.Top());
		used.push_back(deck.Top());
		deck.Pop();

		if (box.getStatus() == Box::Status::BUST 		|| 
			box.getStatus() == Box::Status::BLACKJACK 	||
			box.getStatus() == Box::Status::TWENTY_ONE 	||
			box.getStatus() == Box::Status::FULL)
		{
			++current_box;	
			nextActiveBox();
		}

		return 0;
	}
	else
		return -1;
}

int Game::GamePhase()
{
	current_box = 0;
}

void Game::Sit()
{
	++current_box;
	nextActiveBox();
}

// Deal cards to atleast 17
// Check if busts
// Pay appropriate players
Card Game::FinalDeal()
{
	if (dealer.getCount().first < 17)
	{
		dealer.addCard(deck.Top());
		used.push_back(deck.Top());
		deck.Pop();
		return dealer.Top();
	}
	else
	{
		Payout();
		return Card();
	}
}

void Game::Payout()
{
	if (dealer.Bust())
	{
		// Pay everyone
	}
	else 
	{
		// Pay appropriately
	}	
}

void Game::CleanUp()
{
	for (auto& it : boxes)
		it = Box();
}

void Game::Next()
{
	switch (state)
	{
		case State::PLACE_BETS:
			state = State::INITIAL_DEAL;
			break;
		case State::INITIAL_DEAL:
			break;
	}
}

Player& Game::currentPlayer()
{
	return players[current_player];
}

void Game::Load(const std::string& path)
{
	std::ifstream stream(path, std::ios_base::in);
	players[0].read_form(stream);
}

