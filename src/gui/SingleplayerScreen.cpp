#include <gui/SingleplayerScreen.hpp>

namespace blackjack {


    SingleplayerScreen::SingleplayerScreen(Game& game)
    {
    
    }

    void SingleplayerScreen::Bind(Window* target)
    {
        menu = new Menu(target);
        menu->addItem("New Player");
        menu->addItem("Load Player");
        menu->setPosition(0.5f, 0.5f);
    }

    void SingleplayerScreen::New()
    {
        TextEntry* name_enter = new TextEntry(target);
    
    }
    void SingleplayerScreen::Load()
    {
    
    }




}
