#include <gui/SingleplayerScreen.hpp>
#include <class/Config.hpp>
#include <boost/filesystem.hpp>

using namespace boost::filesystem;

namespace blackjack {

    SingleplayerScreen::SingleplayerScreen(Game& game) : game(game), gui(&game)
    {
    
    }

    void SingleplayerScreen::Initialize()
    {
		target->Clear();
        menu = new Menu(target);

       	for (auto&& p : directory_iterator(path(game::save)))
			if (is_regular_file(p))
				menu->addItem(p.path().filename().string());

        menu->addItem("----------");
        menu->addItem("New Player");

        menu->setPosition(0.5f, 0.5f);
		target->addCommand(10, std::bind(&SingleplayerScreen::Load, this));
    }

    void SingleplayerScreen::New()
    {
        TextEntry* name_enter = new TextEntry(target);
    
    }
    void SingleplayerScreen::Load()
    {
		// Check if last item is selected
		if (menu->getSelectedIndex() == menu->getItems().size() - 1)
			New();
		else
		{
			path potential_save(game::save + menu->getSelectedItem());
			Label* debug = new Label(target, 5, 5);
			debug->setText(potential_save.string());
			if (exists(potential_save))
				game.Load(potential_save.string());
			gui.Bind(target);
		}
    
    }

}
