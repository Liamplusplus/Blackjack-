
#include <ucurses/ucurses.hpp>

using namespace ucurses;

class Game;

namespace blackjack {

    class PlayerCreate : public State
	{
		public:

			PlayerCreate(Game* game);


		protected:

			virtual void Initialize();

			Game* game_data;

			Label* hint;
			TextEntry* name_entry;

	};

}

