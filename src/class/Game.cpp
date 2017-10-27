#include <class/Game.hpp>
#include <class/Config.hpp>

#include <fstream>

Game::Game()
{
    std::fstream logfile(game::log, std::ios_base::out);
    logfile << "Constructing game object" << std::endl;
    for (auto& box : boxes)
        box = Box();
}

void Game::Run()
{
    /* 
     * Choose bet (Enter amount (or quit))
     * Play hand  (Hit or sit)
     * Deal dealers hand
     * Repeat
     */

}

void Game::Deal()
{
   
    for (auto& box : boxes)
    {
        if (box.getSum() > 0.0f)
        {

        }
    }
}

bool Game::addBet(float value, int box)
{
    return boxes[box - 1].addBet(value);
}
