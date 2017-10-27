#include <gui/MainMenu.hpp>
#include <ucurses/gui/Config.hpp>

namespace blackjack {


	MainMenu::MainMenu(Game& game)
	{
	
	}

	void MainMenu::Bind(Window* target)
	{
		mode_select = new Menu(target);
		mode_select->setPosition(0.5f, 0.5f);

		mode_select->addItem("Play");
		mode_select->addItem("Settings");

		target->addCommand(10, std::bind(&MainMenu::Select, this));

		//win->pushCallback(KEY_F(3), std::bind(&MainMenu::Bind, this, target));
		//win->setCallbackTip("F3: Back to Settings");
	}

	void MainMenu::Select()
	{
		switch (mode_select->getSelectedIndex())
		{
			case Selection::GAME:
				//playerScreen();
				break;
			case Selection::SETTINGS:
				Config::Display(win);
				break;
		}
	}
}
