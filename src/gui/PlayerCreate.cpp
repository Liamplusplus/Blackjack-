#include <gui/PlayerCreate.hpp>
#include <class/Game.hpp>

namespace blackjack {

	void CreatePlayer(Window* target, ::Game* game_data)
	{
		target->Clear();
        target->ucurses->Render();
        TextEntry* name_enter = new TextEntry(target);
        name_enter->setPosition(0.5f, 0.5f);
        name_enter->setSubject("Name");
        while (name_enter->getText() == "")
            name_enter->getInput();

        game_data->New(name_enter->getText());
	
	}

}
