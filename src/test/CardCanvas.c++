#include <ucurses/ucurses.hpp>
#include <gui/CardCanvas.hpp>

using namespace ucurses;

int main()
{

    UCurses gui;
	Window* mainwindow = gui.createWindow();

    Card test(5, Card::Suit::HEART);
    gui::CardCanvas* canvas = new gui::CardCanvas(mainwindow, 5, 3);
    canvas->Load(test);

    gui.Run();	
    
}
