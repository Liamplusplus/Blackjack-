#include <gui/MainMenu.hpp>
#include <ucurses/gui/Config.hpp>

namespace blackjack {


	MainMenu::MainMenu(::Game* game) : game_data(game)
	{
	
	}

	void MainMenu::Initialize()
	{
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
        auto lambda = [](Window* target, ::Game* game) { target->Bind(new MainMenu(game)); };
		target->pushCallback(KEY_F(3), std::bind(lambda, target, game_data));

		switch (mode_select->getSelectedIndex())
		{
			case Selection::SP:
				target->Bind(new SingleplayerScreen(game_data));
				break;
			case Selection::SETTINGS:
				target->Bind(new Config());
				break;
		}
	}
}
