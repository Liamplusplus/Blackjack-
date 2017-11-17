#include <gui/MainMenu.hpp>
#include <ucurses/gui/Config.hpp>

namespace blackjack {


	MainMenu::MainMenu(Game& game) : sp(game)
	{
	
	}

	void MainMenu::Initialize()
	{
		target->Clear();
		mode_select = new Menu(target);
		mode_select->setPosition(0.5f, 0.5f);

		mode_select->addItem("Singleplayer");
		mode_select->addItem("Multiplayer");
		mode_select->addItem("Settings");

		target->addCommand(10, std::bind(&MainMenu::Select, this));

		//win->pushCallback(KEY_F(3), std::bind(&MainMenu::Bind, this, target));
		//win->setCallbackTip("F3: Back to Settings");
	}

	void MainMenu::Select()
	{
		target->pushCallback(KEY_F(3), std::bind(&MainMenu::Initialize, this));

		switch (mode_select->getSelectedIndex())
		{
			case Selection::SP:
				sp.Bind(target);
				break;
			case Selection::SETTINGS:
				config_ui.Bind(target);
				break;
		}
	}
}
