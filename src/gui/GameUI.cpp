#include <gui/GameUI.hpp>
#include <gui/CardCanvas.hpp>
#include <class/Config.hpp>
#include <class/Game.hpp>

#include <sstream>
#include <iomanip>

namespace blackjack {

    GameUI::GameUI(::Game* game) : game(game)
    {

    }

    void GameUI::Initialize()
    {

		player_info = new Label(target);
		player_info->setPosition(0.05f, 0.1f);

        bet = new TextEntry(target);
		bet->setPosition(0.5f, 0.95f);
        bet->setSubject("Place Bet");

        for (size_t i = 0; i < boxes.size(); ++i)
        {
            boxes[i] = new Label(target);
			boxes[i]->setPosition(0.1666f * (i + 0.3), 0.8f);
            boxes[i]->setText("  Box " + std::to_string(i + 1));
        }
		
		for (size_t i = 0; i < boxes.size(); ++i)
        {
            counts[i] = new Label(target);
			counts[i]->setPosition(0.1666f * (i + 0.3), 0.76f);
        }

        counts.back() = new Label(target);
		counts.back()->setPosition(0.5f, 0.2f);
        counts.back()->move(15, 3);

        InitialDeal::Setup(this);

    }

	/********** Game States ********/

	// Currently deals cards to every box with money and then draws a cardcanvas
	void GameUI::InitialDeal()
	{
		int boxno = game->InitialDeal();	
	
		if (boxno > -1) // Active Box found
		{
			Box& box = game->box_manager.Get(boxno);
			float x = 0.1666f * (boxno + 0.3);
			float y = 0.55;
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(x, y);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(box.Top());
            game->box_manager.Next();
		}
		else if (boxno == -2) // Dealer turn
		{
			Box& box = game->box_manager.Get(DEALER_BOX);
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(0.5f, 0.2f);
			canvas->Load(box.Top());
		}
		else if (boxno == -3)
		{
			GamePhase();
		}
		RefreshActiveBox();
	}

	/*
	 * Find next active box
	 * Prompt hit or sit
	 * 		If bust or sit, increment box
	 * 		If hit and safe, prompt again
	 *
	 * 	After all boxes, deal dealers hand
	 */
	void GameUI::GamePhase()
	{
		for (int i = 0; i < counts.size(); ++i)
			refreshBoxCount(i);

        if (game->GamePhase() != -1)
        {
            target->clearCommands();
            target->addTip("h: Hit");
            target->addTip("s: Sit");

            // DEBUG
            //
            target->addCommand('l', std::bind(&Game::logState, game));

            target->addCommand('h', std::bind(&GameUI::Hit, this));
            target->addCommand('s', std::bind(&GameUI::Sit, this));
        }
        else
        {
            target->Bind(new GameUI(this->game));
        }
    }

    void GameUI::setup()
    {
        target->clearCommands();

        target->addTip("Enter: Final Deal");
        target->addCommand('l', std::bind(&Game::logState, game));
        target->addCommand(10, std::bind(&GameUI::FinalDeal, this));
    }

    void GameUI::FinalDeal()
    {
        Card card = game->FinalDeal();
        refreshBoxCount(DEALER_BOX);

        if (!card.Null())
        {
            Box& box = game->box_manager.Get(DEALER_BOX);
            CardCanvas* canvas = new CardCanvas(target);
            canvas->setPosition(0.5f, 0.2f);
            canvas->move(0, -(box.nCards()  * 2) + 2);
            canvas->Load(box.Top());
        }
        else
        {
            if (game->getPlayer().getBalance() < 5.f)
            {
                game::debug << "TEST" << std::endl;
                target->Clear();
                Label* game_over = new Label(target);
                game_over->setPosition(0.5f, 0.5f);
                game_over->setText("You are broke, go be depressed somewhere else");
                game_over->move(-10, 0);
                target->addTip("Enter: Accept Defeat");
                target->addCommand(10, std::bind(&InitialDeal::Callback, game, target));
            }
            else
            {
                target->Clear();
                Initialize();
            }
        }
    }

    void GameUI::displayResults()
    {

    }

    void GameUI::displayPlayerInfo(Label* display)
    {
        std::stringstream stream;
        stream << game->getPlayer().getName();
        stream << ": $" << std::fixed << std::setprecision(2) << game->getPlayer().getBalance();
        player_info->setText(stream.str()); 
    }


    // 
    void GameUI::Hit()
    {
        int active = game->Hit();
        if (active != -1)
        {
            float y = 0.55;
            float x = 0.1666f * (active + 0.3);
            CardCanvas* canvas = new CardCanvas(target);
            canvas->setPosition(x, y);
            canvas->move(0, -(game->box_manager.Get(active).nCards()  * 2) + 2);
            canvas->Load(game->box_manager.Get(active).Top());
            refreshBoxCount(active);
            if (game->box_manager.getActiveIndex() == boxes.size())
                setup();
        }
        RefreshActiveBox();
    }

    void GameUI::Sit()
    {
        if (game->Sit() == -1)
            setup();
        RefreshActiveBox();
    }
    // Initial Deal:
    // Deal one card to every box with money in it. Then one card to dealer
    //
    // Game Round
    // Ask each non-empty box to hit or sit, and add a card accordingly
    // Then deal the dealers box, hitting whilst under 17

    void GameUI::placeBet(int boxn)
    {
        game::debug << "placeBet() " << boxn << std::endl;
        bet->getInput();
        std::stringstream bet_amount;
        bet_amount.str(bet->getText());
        if (!bet_amount.str().empty())
        {
            double temp = 0.0f;
            if (bet_amount >> temp)
            {
                if (temp > 0.0f)
                {
                    if (game->addBet(temp, boxn) == -1)
                        bet->setText("Not enough funds");
                }
                else bet->setText("Bet must be greater than zero");
            }
            else
                bet->setText("Invalid bet");
        }
        std::stringstream stream("$");
        stream << game->getPlayer().getName();
        stream << ": $" << std::fixed << std::setprecision(2) <<  game->getPlayer().getBalance();
        player_info->setText(stream.str());
        RefreshBoxes();
    }

    void GameUI::RefreshBoxes()
    {
        for (int i = 0; i < boxes.size(); ++i)
        {
            boxes[i]->setText("  Box " + std::to_string(i + 1) + "  "); // 0, 1, 8, 9
            boxes[i]->appendLine("");
            for (auto& bet : game->box_manager.Get(i).bets)
                if (bet > 0.0f)
                {
                    std::stringstream stream;
                    stream << game->getPlayer().getName() << ": $" << std::fixed << std::setprecision(2) << bet;
                    boxes[i]->appendLine(stream.str());
                }
        }
        RefreshActiveBox();
    }

    // Pass in index to allow updating one box at a time
    void GameUI::refreshBoxCount(int index)
    {
        Box& box = game->box_manager.Get(index);

        std::pair<short, short> count = box.getCount();
        Box::Status status = box.getStatus();

        if (status == Box::Status::BUST)
            counts[index]->setText("--- Bust ---");
        else if (status == Box::Status::UNDER || status == Box::Status::TWENTY_ONE)
        {
            counts[index]->setText(std::to_string(count.first));
            if (count.second != -1)
                counts[index]->appendText(", " + std::to_string(count.second));
        }
        else if (status == Box::Status::BLACKJACK)
            counts[index]->setText("+++ Blackjack +++");
    }

    void GameUI::RefreshGraphics()
    {

    }

    void GameUI::RefreshActiveBox()
    {
        for (auto& it : boxes)
        {
            it->getText()[0] = ' ';
            it->getText()[8] = ' ';
        }

        if (game->box_manager.getActiveIndex() < boxes.size())
        {
            boxes[game->box_manager.getActiveIndex()]->getText()[0] = '*';
            boxes[game->box_manager.getActiveIndex()]->getText()[8] = '*';
        }
    }

    void GameUI::Payout()
    {
        displayPlayerInfo(player_info);

    }
}
