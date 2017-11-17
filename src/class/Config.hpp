#pragma once
#include <string>
#include <fstream>

namespace game {

    const static std::string log = "./log/game.log";
    const static std::string graphics = "./.resources/cards";
	const static std::string save = "./.resources/save/";

	extern std::ofstream debug;
}
