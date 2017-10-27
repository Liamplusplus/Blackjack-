#include <class/Deck.hpp>
#include <class/Config.hpp>

#include <algorithm>
#include <fstream>

Deck::Deck()
{
    for (int value = 1; value <= 13; ++value)
        for (int suit = 0; suit < Card::Suit::NUMSUIT; ++suit)
            deck.emplace_back(value, static_cast<Card::Suit>(suit));
    if (deck.size() != 52)
    {
        std::fstream logfile(game::log, std::ios_base::out);
        logfile << "Error: Deck size is not equal to 52" << std::endl;
    }
}

void Deck::Shuffle()
{
    std::random_shuffle ( deck.begin(), deck.end() );
}

void Deck::write_form(std::ostream& stream)
{
    stream << deck.size() << std::endl;
    for (int i = 0; i < deck.size(); ++i)
        deck[i].write_form(stream);
}
void Deck::read_form(std::istream& stream)
{
    size_t size;
    stream >> size;
    deck.resize(size);
    for (int i = 0; i < deck.size(); ++i)
        deck[i].read_form(stream);
}

void Deck::write_dump(std::ostream& stream)
{
    
}
void Deck::read_dump(std::istream& stream)
{
    
}