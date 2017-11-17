#include <gui/GameUI.hpp>
#include <gui/CardCanvas.hpp>
#include <class/Config.hpp>

#include <sstream>
#include <iomanip>

namespace blackjack {

    GameUI::GameUI(Game* game) : game(game)
    {

    }

    void GameUI::Initialize()
    {
		target->Clear();
        // Split window up into 6. With 40 characters of spacing
        coord x = target->getSize().x - 40;
        coord box_width = x / 6;

		player_info = new Label(target);
		player_info->setPosition(0.05f, 0.1f);
        std::stringstream stream;
        stream << game->currentPlayer().getName();
		stream << ": $" << std::fixed << std::setprecision(2) << game->currentPlayer().getBalance();
		player_info->setText(stream.str());

        target->addTip("1-6: Bet on box");

        bet = new TextEntry(target);
		bet->setPosition(0.5f, 0.95f);
        bet->setSubject("Place Bet");

        for (size_t i = 0; i < boxes.size(); ++i)
        {
            boxes[i] = new Label(target);
			boxes[i]->setPosition(0.1666f * (i + 0.3), 0.8f);
            boxes[i]->addCommand(i + 49, std::bind(&GameUI::placeBet, this, i + 1));
            boxes[i]->setText("  Box " + std::to_string(i + 1));
        }
		boxes[0]->highlightRow(1);
		boxes[2]->highlightRow(1);
		
		for (size_t i = 0; i < boxes.size(); ++i)
        {
            counts[i] = new Label(target);
			counts[i]->setPosition(0.1666f * (i + 0.3), 0.76f);
        }

        target->addTip("Enter: Deal");
		target->addCommand(10, std::bind(&GameUI::InitialDeal, this));
		target->addCommand('l', std::bind(&Game::logState, game));

        RefreshBoxes();
    }

	/********** Game States ********/

	// Currently deals cards to every box with money and then draws a cardcanvas
	void GameUI::InitialDeal()
	{
		int boxno = game->InitialDeal();	
	
		if (boxno > -1) // Active Box found
		{
			Box& box = game->box_manager.getBox(boxno);
			float x = 0.1666f * (boxno + 0.3);
			float y = 0.55;
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(x, y);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(box.Top());
			box.Top().write_form(game::debug);
		}
		else if (boxno == -2) // Dealer turn
		{
			Box& box = game->dealer;
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(0.5f, 0.2f);
			canvas->Load(box.Top());
			game->resetCurrentBox();
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
		for (int i = 0; i < boxes.size(); ++i)
			refreshBoxCount(i);

		game->GamePhase();
		target->clearCommands();
		target->addTip("h: Hit");
		target->addTip("s: Sit");

		// DEBUG
		//
		target->addCommand('l', std::bind(&Game::logState, game));

		target->addCommand('h', std::bind(&GameUI::Hit, this));
		target->addCommand('s', std::bind(&GameUI::Sit, this));
	}

	void GameUI::setup()
	{
		target->clearCommands();

		target->addTip("Enter: Final Deal");
		target->addCommand(10, std::bind(&GameUI::FinalDeal, this));
	}
	
	void GameUI::FinalDeal()
	{
		Card card = game->FinalDeal();

		if (!card.Null())
		{
			Box& box = game->box_manager.dealer;
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(0.5f, 0.2f);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(box.Top());
		}
	}
	

	void GameUI::Hit()
	{
		int next_box = game->box_manager.nextActive();
		Box& box = game->box_manager.getBox(next_box);
		if (game->Hit() != -1)
		{
			float y = 0.55;
			float x = 0.1666f * (next_box + 0.3);
			CardCanvas* canvas = new CardCanvas(target);
			canvas->setPosition(x, y);
			canvas->move(0, -(box.nCards()  * 2) + 2);
			canvas->Load(game->box_manager.getBox(next_box).Top());
			refreshBoxCount(next_box);
		}
		else
			setup();
		RefreshActiveBox();
	}

	void GameUI::Sit()
	{
		game->box_manager.Next();
		game->box_manager.nextActive();
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
		bet->getInput();
		std::stringstream bet_amount;
		bet_amount.str(bet->getText());
		if (!bet_amount.str().empty())
		{
			double temp = 0.0f;
			if (bet_amount >> temp)
			{
				switch (game->box_manager.addBet(temp, boxn))
				{
					case Box::BetErrorCode::INSUFFICIENT_FUNDS:
						bet->setText("Not enough funds");
						break;
					case Box::BetErrorCode::INVALID:
						bet->setText("Invalid bet");
						break;
				}
			}
			else
				bet->setText("Invalid bet");
		}
		std::stringstream stream("$");
		stream << game->currentPlayer().getName();
		stream << ": $" << std::fixed << std::setprecision(2) <<  game->currentPlayer().getBalance();
		player_info->setText(stream.str());
		RefreshBoxes();
	}

	void GameUI::RefreshBoxes()
	{
		for (int i = 0; i < boxes.size(); ++i)
		{
			boxes[i]->setText("  Box " + std::to_string(i + 1) + "  "); // 0, 1, 8, 9
			boxes[i]->appendLine("");
			for (auto& bet : game->box_manager.getBox(i).bets)
				if (bet > 0.0f)
				{
					std::stringstream stream;
					stream << game->currentPlayer().getName() << ": $" << std::fixed << std::setprecision(2) << bet;
					boxes[i]->appendLine(stream.str());
				}
		}
		RefreshActiveBox();
	}

	// Pass in index to allow updating one box at a time
	void GameUI::refreshBoxCount(int index)
	{
		Box& box = game->box_manager.getBox(index);
		std::pair<short, short> count = box.getCount();
		Box::Status status = box.getStatus();

		if (status == Box::Status::BUST)
			counts[index]->setText("--- Bust ---");
		else if (status == Box::Status::UNDER)
		{
			counts[index]->setText(std::to_string(count.first));
			if (count.second != -1)
				counts[index]->appendText(", " + std::to_string(count.second));
		}
		else if (status == Box::Status::TWENTY_ONE)
			counts[index]->setText("Twenty One!");
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

		boxes[game->box_manager.getActiveIndex()]->getText()[0] = '*';
		boxes[game->box_manager.getActiveIndex()]->getText()[8] = '*';
	
	}
}
