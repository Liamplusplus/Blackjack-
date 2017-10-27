#include <class/Card.hpp>
#include <graphics/CardGraphic.hpp>

int main()
{
    Card card(13, Card::Suit::DIAMOND);
    graphics::CardDisplay display;
    graphics::LoadGraphic(card, display);

    Card card2(10, Card::Suit::SPADE);
    graphics::CardDisplay display2;
    graphics::LoadGraphic(card2, display2);

    for (auto& it : display)
        std::cout << it;
    std::cout << std::endl;

    for (auto& it : display2)
        std::cout << it;
}

