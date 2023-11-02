#include <iostream>
#include <thread>
#include "Game.hpp"

/**
 * @brief Makes a string lowercase
 * 
 * @param input String to make lowercase
 * @return std::string 
 */
std::string toLowercase(const std::string &input)
{
	std::string result = input;
	for (char &c : result) {
		c = std::tolower(c);
	}
	return result;
}

/**
 * @brief Gets character, and if true, it will exit from the program.
 * 
 */
void getExitInput()
{
	std::cout << "Type \"q\", \"exit\" or \"quit\" to quit the game." << '\n';
	std::string in;
	while (true) {
		std::getline(std::cin, in);
		std::string in_lower = toLowercase(in);
		if (in_lower == "q" || in_lower == "exit" || in_lower == "quit") {
			std::cout << "Exiting..." << '\n';
			std::exit(0);
		}
	}
}

void runGame()
{
	Game game;
	game.Run();
}

int main(int argc, char *argv[])
{
	try {
		std::thread game(runGame);
		std::thread input(getExitInput);
		game.join();
		input.join();
	}

	catch (std::exception const &e) {
		std::cerr << e.what();
	}

	return 0;
}
