/*
 * Contains 52 Unique cards
 * Shuffles every hand
 */

#pragma once
#include <vector>
#include <class/Card.hpp>
	
namespace ctk { class RandomGenerator; }

class Deck
{
    public:

        Deck(); 

        void Shuffle(ctk::RandomGenerator& rand_gen);

		// I/O
		//
        void write_form(std::ostream& stream);
        void read_form(std::istream& stream);
    
        void write_dump(std::ostream& stream);
        void read_dump(std::istream& stream);
    
        void write_binary(std::ostream& stream) {}
        void read_binary(std::istream& stream)  {}

		Card& Top() { return deck.back(); }
		void  Pop() { deck.pop_back(); }

    protected:

        // Last element of the array is the top of the deck
        // std::stack does not expose iterators
        std::vector<Card> deck;
};
