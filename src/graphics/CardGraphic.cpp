#pragma once
#include <graphics/CardGraphic.hpp>
#include <class/Config.hpp>
#include <fstream>
#include <algorithm>

namespace graphics {

    void LoadGraphic(const Card& card, CardDisplay& canvas)
    {
        // Newline positions are known. Just jump to start of desired card
        std::ifstream file(game::graphics, std::ios_base::in);
        file.seekg((card.value - 1) * 108);

        file.read(canvas.data(), 108);
        LoadSuitGraphic(card, canvas);
    }
    
    void LoadSuitGraphic(const Card& card, CardDisplay& canvas)
    {
        if (card.suit != Card::Suit::HEART)
            for (auto& it : canvas)
                if (it == 'H')
                    it = suit_symbols[card.suit];
    
    }
}
