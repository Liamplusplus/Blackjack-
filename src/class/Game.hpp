/*
 * Handle all logic and ensure the rules are carried out
 *
 */

#pragma once
#include <fstream>
#include <array>

#include <class/Deck.hpp>
#include <class/Box.hpp>
#include <class/Player.hpp>

class Game
{
    public:

		enum BetErrorCode { SUCCESS = 0, INSUFFICIENT_FUNDS, MAX_CAPACITY, INVALID };
        Game();

        void Deal();
        void Run();

        BetErrorCode addBet(float value, int box);
        
        Deck deck;
		std::vector<Card> used;

        std::array<Box, 6> boxes;


		Player player;


};
