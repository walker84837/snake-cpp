#include <iostream>
#include "Game.hpp"

int main(int argc, char *argv[])
{
	Game game;
	game.Run();
	try
	{
		game.Run();
		std::cout << "Game has terminated successfully, score: " << game.GetScore() << ", size: " << game.GetSize() << "\n";
	}
	catch (std::exception const &e)
	{
		std::cerr << e.what();
	}
	return 0;
}