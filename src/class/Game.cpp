#include <class/Game.hpp>
#include <class/Config.hpp>

#include <fstream>
#include <algorithm>

Game::Game() : active(false)
{
	initial_state = InitialState::FIRST_ROUND;

    deck.Shuffle(rand_gen);
}

void Game::Save()
{
    std::fstream file(game::save + player.getName(), std::ios_base::binary);
    player.write_binary(file);
}

// Interuptable initial deal phase
// Add card to next active box
// if no active boxes prompt player
// If none return error
// if current_box == 5 && round == first
// deal dealer then set round to second
// else start game phase
//
int Game::InitialDeal()
{
	int active_box = box_manager.nextActive();
    Box& box = box_manager.getActive();
    if (active_box != -1)
    {
        active = true;
        box_manager.addCard(deck.Top());
        deck.Pop();

        if (box.getStatus() == Box::Status::BLACKJACK)
            Pay(active_box, 2.5f);

        return active_box;
    }
    else if (!active)
    {
        box_manager.setActive(0);
        return -1; // No bets have been placed
    }
    else if (initial_state == InitialState::FIRST_ROUND)
    {
        box_manager.Get(DEALER_BOX).addCard(deck.Top());
        deck.Pop();
        initial_state = InitialState::SECOND_ROUND;

        // Deal second card to each active box
        box_manager.setActive(0);
        return -2;
    }
    else
        return -3;

    if (box_manager.nextActive() == -1 && initial_state == InitialState::SECOND_ROUND)
        return -3;
}



void Game::logState()
{
    std::ofstream stream("./log/game_state", std::ios_base::out);
    stream << "<Gamestate>\n";

    box_manager.write_form(stream);

    player.write_form(stream);
    stream << '\n';
}

// Go to next active box, if active add card
// Need to check for instant payout or bust
int Game::Hit()
{
    if ( box_manager.nextActive() != -1)
    {
        int _active = box_manager.addCard(deck.Top());
        deck.Pop();

        if (box_manager.Get(_active).getStatus() == Box::Status::FULL)
            Pay(_active, 2.f);

        return _active;
    }
    else
        return -1;

}

void Game::Pay(int box_index, float factor)
{
    Box& box = box_manager.Get(box_index);
    for (int i = 0; i < box.bets.size(); ++i)
    {
        float amount = box.bets[i];
        if (amount > 0.0f)
            player.Pay(amount * factor);
    }
    box.setActive(false);
    
}

int Game::GamePhase()
{
    if (box_manager.anyActive())
    {
        box_manager.setActive(0);
        box_manager.nextActive();
        return 0;
    }
    else
    {
        Reset();
        return -1;
    }
}

int Game::Sit()
{
    box_manager.Next(); 
    return box_manager.nextActive();
}

// Deal cards to atleast 17
// Check if busts
// Pay appropriate players
Card Game::FinalDeal()
{
    Box& dealer = box_manager.Get(DEALER_BOX);
    if (box_manager.anyActive())
    {
        if (dealer.Highest() < 17)
        {
            dealer.addCard(deck.Top());
            deck.Pop();
            return dealer.Top();
        }
        else
        {
            Payout();
            Reset();
            return Card();
        }
    }
    else
    {
        Reset();
        return Card();
    }
}

void Game::Payout()
{
    box_manager.setActive(0);
    Box& dealer = box_manager.Get(DEALER_BOX);
    // If dealer busts pay all
    if (dealer.Bust())
    {
        while (box_manager.nextActive() != -1)
        {
            Pay(box_manager.getActiveIndex(), 2.f);
            box_manager.Next();
        }
    }
    else if (!box_manager.Get(DEALER_BOX).getStatus() == Box::Status::BLACKJACK)
    {
        // Pay appropriately
        while (box_manager.nextActive() != -1)
        {
            Box& box = box_manager.getActive();
            // Win
            if (box.Highest() > dealer.Highest())
                Pay(box_manager.getActiveIndex(), 2.f);

            // Standoff
            if (box.Highest() == dealer.Highest())
                Pay(box_manager.getActiveIndex(), 1.f);

            box_manager.Next();
        }
    }	
}

// Empty all boxes and shuffle deck
void Game::Reset()
{
    active = false;
	initial_state = InitialState::FIRST_ROUND;
    deck.Reset(rand_gen);
    box_manager.Reset();
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

Player& Game::getPlayer()
{
    return player;
}

void Game::Load(const std::string& path)
{
    std::ifstream stream(path, std::ios_base::in);
    player.read_form(stream);
}

int Game::addBet(float value, int box)
{
    int pos = box - 1; // Offset created by box numbers
    if (player.getBalance() >= value && value > 0.0f)
    {
        box_manager.addBet(value, pos);
        player.setBalance(player.getBalance() - value);
        return 0;
    }
    else
    {
        return -1;
    }

}

