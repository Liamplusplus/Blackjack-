#pragma once
#include <iostream>
#include <string>

struct Card
{
    // Constants and enums
    enum Suit { HEART = 0, DIAMOND = 1, SPADE = 2, CLUB = 3, NUMSUIT };
    enum Special { ACE = 0, JACK = 1, QUEEN = 2, KING = 3, NUMSPECIAL };

    // Data 
    int value; 
    Suit suit;

    Card(int value, Suit suit) : value(value), suit(suit) {}
    Card() : value(0) {}

	bool Null() { return value == 0; }


    // Methods
    void write_form(std::ostream& stream) const;
    void read_form(std::istream& stream);
    
    void write_dump(std::ostream& stream) const;
    void read_dump(std::istream& stream);
    
    void write_binary(std::ostream& stream) {}
    void read_binary(std::istream& stream) {}
};

static const std::string suit_names[Card::Suit::NUMSUIT] = { "Hearts", "Diamonds", "Spades", "Clubs" };
static const std::string special_names[Card::Special::NUMSPECIAL] = { "Ace", "Jack", "Queen", "King" };
