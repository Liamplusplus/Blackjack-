/*
 * Stores bets and cards
 */

#pragma once

#include <utility>
#include <array>

#include <class/Card.hpp>

class Box
{
    public:

		enum BetErrorCode 	{ SUCCESS = 0, INSUFFICIENT_FUNDS, MAX_CAPACITY, INVALID };
		enum Status 		{ BLACKJACK, TWENTY_ONE, BUST, UNDER, FULL };
        Box();

        // Returns sum of all bets
        float getSum();

		Status getStatus();
		// Determine status of box
		void setStatus();

        std::pair<short, short> getCount();
		// Two possible values
		// Every ace is a one || One ace is an 11
		// getCount().first being the safest and
		// getCount().second being the highest
		// getCount().second == -1 if over 22 or no aces exist

		void addCard(Card& card);
		Card Bottom();				// Returns the first non-null card
		Card Top();
	
		// Hands
		bool Bust();				/* Too many */
		bool Blackjack();

		bool Empty();				/* No cards */
		bool inActive();			/* No bets */
		int nCards();
        
		bool addBet(float f);		// Returns false if box is full

		// Assume the player at index 0 is owner of bets[0]
		// This removes the need to map players to the bets they place
		// But it also ties the number of players to the number of bets a box can hold
		//
        std::array<float, 4> bets;

		void write_form(std::ostream& stream);


    protected:

        std::array<Card, 5> cards;
		Status status;
};

