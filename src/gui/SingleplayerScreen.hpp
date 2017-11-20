/*
 *
 */

#pragma once

#include <ucurses/ucurses.hpp>
using namespace ucurses;

class Game;

namespace blackjack {

    class SingleplayerScreen : public ucurses::State
    {
        public:

            SingleplayerScreen(::Game* game);

            void New();
            void Load();

        protected:

            virtual void Initialize();

            Menu* menu;
            coord2d pos = coord2d(0,0);
			Game* game_data;
    
    };
}
