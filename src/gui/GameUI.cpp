#include <gui/GameUI.hpp>
#include <sstream>
namespace gui {

    GameUI::GameUI(Game& game) : game(game)
    {

    }

    void GameUI::Bind(Window* win)
    {
        // Split window up into 6. With 40 characters of spacing
        coord x = win->getSize().x - 40;
        coord box_width = x / 6;

		player_info = new Label(win);
		player_info->setPosition(0.05f, 0.1f);
		player_info->setText(game.player.name + ": " + std::to_string(game.player.balance));

        win->addTip("1-6: Bet on box");

        bet = new TextEntry(win);
		bet->setPosition(0.5f, 0.90f);
        bet->setSubject("Place Bet");

        for (size_t i = 0; i < boxes.size(); ++i)
        {
            boxes[i] = new Label(win);
			boxes[i]->setPosition(0.1666f * (i + 0.5), 0.8f);
            boxes[i]->addCommand(i + 49, std::bind(&GameUI::placeBet, this, i + 1));
        }

        for (int i = 0; i < boxes.size(); ++i)
            boxes[i]->setText("Box " + std::to_string(i + 1));

        RefreshBoxes();
    }

	void GameUI::Deal()
	{
		Card next_card = game.Deal();	
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
					case BetErrorCode::INSUFFICIENT_FUNDS:
                		bet->setText("Not enough funds");
						break;
					case BetErrorCode::INVALID:
                		bet->setText("Invalid bet");
						break;
				}
			}
            else
                bet->setText("Invalid bet");
        }
		player_info->setText(game.player.name + ": " + std::to_string(game.player.balance));
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
                    boxes[i]->appendLine(std::to_string(bet));
        }
    }
}
