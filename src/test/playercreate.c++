#include <gui/PlayerCreate.hpp>
#include <class/Player.hpp>

int main()
{
   	UCurses gui;
	Window* mainwindow = gui.createWindow();


	Player player;
	gui::PlayerCreate interface(player);
	interface.Bind(mainwindow);

	gui.Run(); 
}
