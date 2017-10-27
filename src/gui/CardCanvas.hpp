
#pragma once
#include <ucurses/component/Component.hpp>
#include <graphics/CardGraphic.hpp>

using namespace ucurses;

namespace gui {

    // Very specific I know. Time constraints
    class CardCanvas : public Component
    {
        public:

            CardCanvas(Window* target, coord x = 0, coord y = 0);
            void Load(const Card& card);
            virtual void Draw();

        protected:

            std::array<char, 108> data;
            void LoadSuit(const Card& card);

    };

}
