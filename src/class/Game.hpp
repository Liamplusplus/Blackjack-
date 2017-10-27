/*
 * Handle all logic and ensure the rules are carried out
 *
 */

#pragma once
#include <fstream>
#include <array>

#include <class/Deck.hpp>
#include <class/Box.hpp>

class Game
{
    public:

        Game();

        void Deal();
        void Run();

        bool addBet(float value, int box);
        
        Deck deck;

        std::array<Box, 6> boxes;
};
