#include <gui/SingleplayerScreen.hpp>
#include <gui/GameUI.hpp>

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

#include <class/Game.hpp>
#include <class/Config.hpp>

namespace blackjack {

    SingleplayerScreen::SingleplayerScreen(::Game* game) : game_data(game)
    {
    
    }

    void SingleplayerScreen::Initialize()
    {
        menu = new Menu(target);

        menu->addItem("New Player");
        menu->addItem("----------");

		if (game_data->save_exists())

       	for (auto&& p : directory_iterator(path(game::save)))
			if (is_regular_file(p))
				menu->addItem(p.path().filename().string());


        menu->setPosition(0.5f, 0.5f);
		target->addCommand(10, std::bind(&SingleplayerScreen::Load, this));
    }

    void SingleplayerScreen::New()
    {
        target->Clear();
        target->ucurses->Render();
        TextEntry* name_enter = new TextEntry(target);
        name_enter->setPosition(0.5f, 0.5f);
        name_enter->setSubject("Name");
        while (name_enter->getText() == "")
            name_enter->getInput();

        game_data->New(name_enter->getText());
        target->Bind(new GameUI(game_data));
        
    
    }

}
