#include <gui/GameUI.hpp>


int main()
{
   	UCurses gui;
	Window* mainwindow = gui.createWindow();


    Game game;
    gui::GameUI interface(game);
	interface.Bind(mainwindow);

	gui.Run(); 
}
