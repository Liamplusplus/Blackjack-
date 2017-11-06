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
        /*
         * Each player places bets
         * Deals first card to players and dealer. Deals second card to all players.
         * Playing phase for all players
         * Dealing phase
         */

        BetErrorCode addBet(float value, int box);
        
        Deck deck;
		std::vector<Card> used;

        std::array<Box, 6> boxes;

        std::array<Player, 4> players;
        Player& currentPlayer();

        int current_player;
        /*
         * Everytime a player finishes betting phase
         * or finshes box this is incremented]
         */

};
