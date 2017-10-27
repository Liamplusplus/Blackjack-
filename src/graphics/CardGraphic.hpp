#pragma once
#include <class/Card.hpp>
#include <array>

namespace graphics {

    // 12 * 9 canvas of chars
    typedef std::array<char, 108> CardDisplay;

    static const char suit_symbols[Card::Suit::NUMSUIT] = {'H', 'D', 'S', 'C'};

    void LoadGraphic(const Card& card, CardDisplay& canvas);
    void LoadSuitGraphic(const Card& card, CardDisplay& canvas);
}
