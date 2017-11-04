#pragma once
#include <array>

#include <class/Game.hpp>

#include <ucurses/ucurses.hpp>
using namespace ucurses;

namespace gui {

    class GameUI : public Interface
    {

        public:

            GameUI(Game& game);

            virtual void Bind(Window* win);


        protected:

			// Widgets
            std::array<Label*, 6> boxes;
            TextEntry* bet;
			Label* player_info;

            Game& game;

            void placeBet(int boxn);
            void RefreshBoxes();

			void Deal();
    
    };

}
