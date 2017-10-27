/*
 * Contains 52 Unique cards
 * Shuffles every hand
 */

#pragma once
#include <vector>
#include <class/Card.hpp>

class Deck
{
    public:

        Deck(); 

        void Shuffle();

        void write_form(std::ostream& stream);
        void read_form(std::istream& stream);
    
        void write_dump(std::ostream& stream);
        void read_dump(std::istream& stream);
    
        void write_binary(std::ostream& stream) {}
        void read_binary(std::istream& stream)  {}

    protected:

        // Last element of the array is the top of the deck
        // std::stack does not expose iterators
        std::vector<Card> deck;

};
