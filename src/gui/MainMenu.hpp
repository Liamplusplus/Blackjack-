/*
 * Main menu
 */

#include <ucurses/ucurses.hpp>
using namespace ucurses;

#include <class/Game.hpp>
#include <gui/SingleplayerScreen.hpp>

namespace blackjack {

	class MainMenu : public ucurses::State
	{
        enum Selection { SP = 0, MP, SETTINGS};

		public:

			MainMenu(Game* game);

		protected:

			void Select();
			virtual void Initialize();

			Menu* mode_select;
            Game* game_data;
	};

}
