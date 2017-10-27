#include <gui/MainMenu.hpp>


int main()
{
   	UCurses gui;
	Window* mainwindow = gui.createWindow();


    Game game;
    blackjack::MainMenu* interface = new blackjack::MainMenu(game);
	interface->Bind(mainwindow);

	gui.Run(); 
}
