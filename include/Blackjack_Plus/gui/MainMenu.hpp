/*
 * Main menu
 */

#include <ucurses/ucurses.hpp>
using namespace ucurses;

#include <class/Game.hpp>
#include <gui/SingleplayerScreen.hpp>

namespace blackjack {

	class MainMenu : public Interface
	{
        enum Selection { SP = 0, MP, SETTINGS};

		public:

			MainMenu(Game& game);
			void Bind(Window* target);

		protected:

			void Select();

			Menu* mode_select;
            SingleplayerScreen sp;
	};

}
