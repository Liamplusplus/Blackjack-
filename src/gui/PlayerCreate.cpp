#include <gui/PlayerCreate.hpp>
#include <class/Game.hpp>

namespace blackjack {


	PlayerCreate::PlayerCreate(Game* game) : game_data(game)
	{
	
	}

	void PlayerCreate::Initialize()
	{
		hint = new Label(target);
		name_entry = new TextEntry(target);

		hint->setText("What is your name?");
		name_entry->setSubject("Name");
		name_entry->addCommand('e', std::bind(&TextEntry::getInput, name_entry));

		
		hint->setPosition(0.5f, 0.5f);
		name_entry->setPosition(hint->getPosition().x, hint->getPosition().y + 1);
	}
}
