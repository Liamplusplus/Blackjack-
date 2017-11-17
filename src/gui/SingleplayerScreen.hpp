/*
 *
 */

#pragma once

#include <ucurses/ucurses.hpp>
using namespace ucurses;

#include <class/Game.hpp>
#include <gui/GameUI.hpp>

namespace blackjack {

    class SingleplayerScreen : public Interface
    {
        public:

            SingleplayerScreen(Game& game);

            void New();
            void Load();

        protected:

            virtual void Initialize();

            Menu* menu;
            coord2d pos = coord2d(0,0);
			Game& game;
			GameUI gui;
    
    };
}
