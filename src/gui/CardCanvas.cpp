#include <gui/CardCanvas.hpp>
#include <class/Config.hpp>

namespace gui {

            
    CardCanvas::CardCanvas(Window* target, coord x, coord y) : Component(target, x, y)
    {
    
    }

    void CardCanvas::Load(const Card& card)
    {
        // Newline positions are known. Just jump to start of desired card
        std::ifstream file(game::graphics, std::ios_base::in);
        file.seekg((card.value - 1) * 108);

        file.read(data.data(), 108);
        std::ofstream ofile("log/card_canvas", std::ios_base::out);
		card.write_form(ofile);
        LoadSuit(card);
    }
    
    void CardCanvas::LoadSuit(const Card& card)
    {
        if (card.suit != Card::Suit::HEART)
            for (auto& it : data)
                if (it == 'H')
                    it = graphics::suit_symbols[card.suit];
    }

    void CardCanvas::Draw()
    {
        setCursor();
        std::fstream log("./test", std::ios_base::out);
        /*
        for (int y = 0; y < 9; ++y)
        {
			setCursor(0, y);
            for (int x = 0; x < 12; ++x)
                print(data[x + (y * 12)]);
        }
        */
        for (int i = 0; i < 108; ++i)
        {
            if (data[i] != '\n')
                print(data[i]);
            else
			    setCursor(0, i / 11);
        }
    }

}
