#include <class/Game.hpp>

#include <ucurses/ucurses.hpp>

using namespace ucurses;


namespace blackjack {

    class PlayerCreate : public Interface
	{
		public:

			PlayerCreate(Game& game);


		protected:

			virtual void Initialize();

			Game& game;

			Label* hint;
			TextEntry* name_entry;

	};

}

