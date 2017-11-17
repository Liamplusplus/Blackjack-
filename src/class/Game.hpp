/*
 * Handle all logic and ensure the rules are carried out
 *
 */

#pragma once
#include <fstream>
#include <array>

#include <class/Deck.hpp>
#include <class/BoxManager.hpp>
#include <class/Player.hpp>

#include <ctk/random/RandomGenerator.hpp>

class Game
{
    public:

		enum class State 			{ PLACE_BETS = 0, INITIAL_DEAL, PLAY, DEAL, PAY}; 
		enum class InitialState		{ FIRST_ROUND = 0, DEALER, SECOND_ROUND };
		enum class FinalState		{ DEAL, PAYOUT };
        Game();

		/* Game Flow */

        int InitialDeal();
		InitialState initial_state;
		int GamePhase();
		Card FinalDeal();
		void Payout();

		void Quit();
		void Save();
		void Next();

		// Empties all boxes and resets statuses
		// Called on quit and at the end of each hand
		void CleanUp();

        void Run();
        /*
         * Each player places bets
         * Deals first card to players and dealer. Deals second card to all players.
         * Playing phase for all players
         * Dealing phase
         */

		int Hit();
		void Sit();

		/* Components */

        Deck deck;
		std::vector<Card> used;

		BoxManager box_manager;

		/* Players */

		Player& currentPlayer();

		void Load(const std::string& path);

		void logState();

	protected:

		std::array<Player, 4> players;

		State state;

		int current_player;

		ctk::RandomGenerator rand_gen;

		bool active;
};
