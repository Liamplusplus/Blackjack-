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

		enum Status 		{ BLACKJACK, TWENTY_ONE, BUST, UNDER, FULL };
        Box();

        // Returns sum of all bets
        float getSum();

		Status getStatus();
		// Determine status of box
		void setStatus();
        bool Active();
        void setActive(bool b);

        std::pair<short, short> getCount();
		// Two possible values
		// Every ace is a one || One ace is an 11
		// getCount().first being the safest and
		// getCount().second being the highest
		// getCount().second == -1 if over 22 or no aces exist
        // Returns highest score under 21
        short Highest();

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
        void Pay(float factor);

		// Assume the player at index 0 is owner of bets[0]
		// This removes the need to map players to the bets they place
		// But it also ties the number of players to the number of bets a box can hold
		//
        std::array<float, 4> bets;

		void write_form(std::ostream& stream);


    protected:

        std::array<Card, 5> cards;
		Status status;

        bool active;
        // Set to true on InitialDeal phase if sum is greater than zero
        // Set to inactive if already payed out due to blackjack
};

