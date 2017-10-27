/*
 * Main menu
 */

#include <ucurses/ucurses.hpp>
using namespace ucurses;

#include <class/Game.hpp>

namespace blackjack {

	class MainMenu : public Interface
	{
        enum Selection { GAME = 0, SETTINGS};

		public:

			MainMenu(Game& game);
			void Bind(Window* target);


		protected:

			void Select();

			Menu* mode_select;
	};

}
