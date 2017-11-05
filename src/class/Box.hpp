#pragma once

#include <utility>
#include <array>

#include <class/Card.hpp>

class Box
{
    public:


        Box();


        // Returns sum of all bets
        float getSum();

        std::pair<short, short> getCount();
        // Second value is used if an ace is used as a one
        // Two aces cannot be 11

        // Returns false if box is full
        bool addBet(float f);
		void addCard(Card& card);
        std::array<float, 4> bets;

		Card Top();
		bool Empty() 	{ return cards[0].Null(); }

    protected:

        std::array<Card, 5> cards;
};
