#include <gui/MainMenu.hpp>


int main()
{
   	UCurses gui;
	Window* mainwindow = gui.createWindow();


    Game game;
    blackjack::MainMenu main_menu(game);
	main_menu.Bind(mainwindow);

	gui.Run(); 
}
