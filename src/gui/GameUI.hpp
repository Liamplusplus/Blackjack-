#pragma once
#include <array>

#include <class/Game.hpp>

#include <ucurses/ucurses.hpp>
using namespace ucurses;

namespace blackjack {

    class GameUI : public Interface
    {

        public:

            GameUI(Game* game);

			// Game states
			void Hit();
			void Sit();
			void FinalDeal();
			void setup();
			void GamePhase();
			void InitialDeal();

        protected:

            void Initialize();

			// Widgets
            std::array<Label*, 6> boxes;
            std::array<Label*, 6> counts;
            TextEntry* bet;
			Label* player_info;

            Game* game;

            void placeBet(int boxn);


			void RefreshGraphics();
            void RefreshBoxes();
            void refreshBoxCount(int index);

			// Everytime box changes update UI to display active box
			void RefreshActiveBox();
    };

}
