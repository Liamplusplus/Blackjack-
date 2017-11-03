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

    void GameUI::placeBet(int boxn)
    {
        bet->getInput();
        std::stringstream bet_amount;
        bet_amount.str(bet->getText());
        if (!bet_amount.str().empty())
        {
            double temp = 0.0f;
            if (bet_amount >> temp)
                game.addBet(temp, boxn);
            else
                bet->setText("Invalid bet");
        }
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
