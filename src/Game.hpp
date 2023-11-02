#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <vector>

using json = nlohmann::json;

class Game
{

      public:
	void loadConfig()
	{
		try {
			if (!std::filesystem::exists("config.json")) {
				throw std::runtime_error(
					"File \"config.json\" doesn't exist."
				);
			}
		}

		catch (std::runtime_error &error) {
			std::cerr << "Error: " << error.what();
			std::exit(1);
		}
		std::ifstream config("config.json");
		json data = json::parse(config);

		const int fpsmax =
		    (static_cast<int>(data["maxfps"]) - 1) * 0.75;
		const int width = static_cast<int>(data["width"]);
		const int height = static_cast<int>(data["height"]);

		FRAME_RATE = 1000 / fpsmax;
		SCREEN_WIDTH = width;
		SCREEN_HEIGHT = height;
	}

	Game();
	void Run();
	int GetScore();
	int GetSize();

      private:
	bool running = false;
	bool alive = false;
	int fps = 0;

	/**
	 * TODO: Change the code so when grid dimensions adapt to new screen
	 * dimensions
	 */

	int FRAME_RATE;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	static const int GRID_WIDTH = 32;
	static const int GRID_HEIGHT = 32;

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;

	enum class Block { head, body, food, empty };
	enum class Move { up, down, left, right };

	Move last_dir = Move::up;
	Move dir = Move::up;

	struct {
		float x = GRID_WIDTH / 2, y = GRID_HEIGHT / 2;
	} pos;

	SDL_Point head = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
	SDL_Point food;
	std::vector<SDL_Point> body;

	Block grid[GRID_WIDTH][GRID_HEIGHT];

	float speed = 0.5f;
	int growing = 0;
	int score = 0;
	int size = 1;

	void EndGame();
	void ReplaceFood();
	void GrowBody(int quantity);
	void GameLoop();
	void Render();
	void Update();
	void PollEvents();
	void Close();
};
