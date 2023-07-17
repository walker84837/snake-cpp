#include <iostream>
#include <thread>
#include "Game.hpp"

void getExitInput()
{
	std::string in;
	while (true)
	{
		std::getline(std::cin, in);
		if (in == "q" || in == "exit" || in == "quit")
		{
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
	try
	{
		std::thread game(runGame);
		std::thread input(getExitInput);
		game.join();
		input.join();
	}

	catch (std::exception const &e)
	{
		std::cerr << e.what();
	}

	return 0;
}