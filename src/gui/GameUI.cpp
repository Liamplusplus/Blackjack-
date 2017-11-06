#include <gui/GameUI.hpp>
#include <gui/CardCanvas.hpp>

#include <sstream>
#include <iomanip>

namespace gui {

    GameUI::GameUI(Game& game) : game(game)
    {

    }

    void GameUI::Bind(Window* win)
    {
		target = win;
        // Split window up into 6. With 40 characters of spacing
        coord x = win->getSize().x - 40;
        coord box_width = x / 6;

		player_info = new Label(win);
		player_info->setPosition(0.05f, 0.1f);
        std::stringstream stream;
        stream << game.players[0].name << ": $" << std::fixed << std::setprecision(2) << game.players[0].balance;
		player_info->setText(stream.str());

        win->addTip("1-6: Bet on box");

        bet = new TextEntry(win);
		bet->setPosition(0.5f, 0.90f);
        bet->setSubject("Place Bet");

        for (size_t i = 0; i < boxes.size(); ++i)
        {
            boxes[i] = new Label(win);
			boxes[i]->setPosition(0.1666f * (i + 0.3), 0.8f);
            boxes[i]->addCommand(i + 49, std::bind(&GameUI::placeBet, this, i + 1));
        }

        win->addTip("Enter: Deal");
		win->addCommand(10, std::bind(&GameUI::Deal, this));

        for (int i = 0; i < boxes.size(); ++i)
            boxes[i]->setText("Box " + std::to_string(i + 1));

        RefreshBoxes();
    }

	void GameUI::Deal()
	{
		// PSEUDO
		// Deal cards
		// Add Canvas for each box with a new card
		game.Deal();	
		
		for (int i = 0; i < game.boxes.size(); ++i)
		{
			Box& box = game.boxes[i];
			if (!box.Empty())
			{
				std::ofstream file("./box.log", std::ios_base::out);
				file << "Adding canvas for box " << i;
				float x = 0.1666f * (i + 0.3);
				float y = 0.65;
				CardCanvas* canvas = new CardCanvas(target);
				canvas->setPosition(x, y);
				canvas->Load(box.Top());
                box.Top().write_form(file);
			}
		}
	
		// Draw card in the right position
	}

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
				switch (game.addBet(temp, boxn))
				{
					case Game::BetErrorCode::INSUFFICIENT_FUNDS:
                		bet->setText("Not enough funds");
						break;
					case Game::BetErrorCode::INVALID:
                		bet->setText("Invalid bet");
						break;
				}
			}
            else
                bet->setText("Invalid bet");
        }
        std::stringstream stream("$");
        stream << game.players[0].name << ": $" << std::fixed << std::setprecision(2) <<  game.players[0].balance;
		player_info->setText(stream.str());
        RefreshBoxes();
    }

    void GameUI::RefreshBoxes()
    {
        for (int i = 0; i < boxes.size(); ++i)
        {
            boxes[i]->setText("Box " + std::to_string(i + 1));
            boxes[i]->appendLine("");
            for (auto& bet : game.boxes[i].bets)
                if (bet > 0.0f)
                {
                    std::stringstream stream;
                    stream << game.players[0].name << ": $" << std::fixed << std::setprecision(2) << bet;
                    boxes[i]->appendLine(stream.str());
                }
        }
    }

	void GameUI::RefreshGraphics()
	{
	
	}
}
