#pragma once
#include <array>

#include <class/Game.hpp>

#include <ucurses/ucurses.hpp>
using namespace ucurses;

namespace gui {

    class GameUI : public ucurses::Interface
    {

        public:

            GameUI(Game& game);

            virtual void Bind(Window* win);


        protected:

            std::array<Label*, 6> boxes;

            TextEntry* bet;

            Game& game;

            void placeBet(int boxn);
            void RefreshBoxes();
    
    };

}
