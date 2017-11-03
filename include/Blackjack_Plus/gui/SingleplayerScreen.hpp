/*
 *
 */

#pragma once

#include <ucurses/ucurses.hpp>
using namespace ucurses;

#include <class/Game.hpp>

namespace blackjack {

    class SingleplayerScreen : public Interface
    {
        public:

            SingleplayerScreen(Game& game);
            void Bind(Window* target);

            void New();
            void Load();


        protected:

            Menu* menu;
            coord2d pos = coord2d(0,0);
    
    };
}
