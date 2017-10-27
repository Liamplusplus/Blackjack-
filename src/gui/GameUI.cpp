#include <gui/GameUI.hpp>

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

        bet = new TextEntry(win, win->getMiddle().x - 8, 55);
        bet->setSubject("Place Bet");

        for (size_t i = 0; i < boxes.size(); ++i)
        {
            boxes[i] = new Label(win, box_width * (i + 1), 50);
            boxes[i]->addCommand(i + 49, std::bind(&GameUI::placeBet, this, i + 1));
        }

        for (int i = 0; i < boxes.size(); ++i)
            boxes[i]->setText("Box " + std::to_string(i + 1));

        RefreshBoxes();
    }

    void GameUI::placeBet(int boxn)
    {
        bet->getInput();
        std::string bet_amount = bet->getText();
        if (!bet_amount.empty())
            game.addBet(std::stod(bet->getText()), boxn);
        RefreshBoxes();
    }

    void GameUI::RefreshBoxes()
    {
        for (int i = 0; i < boxes.size(); ++i)
        {
            boxes[i]->setText("Box " + std::to_string(i + 1));
            for (auto& bet : game.boxes[i].bets)
                if (bet > 0.0f)
                    boxes[i]->appendLine(std::to_string(bet));
        }
    }
}
