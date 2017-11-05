#pragma once
#include <string>
#include <fstream>

namespace game {

    const static std::string log = "./log/game.log";
	static std::ofstream file_log;
    const static std::string graphics = "./.resources/cards";
}
