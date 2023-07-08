#include <iostream>
#include <string>
#include <random>
#include <SDL.h>
#include "Game.hpp"

Game::Game()
{
	for (int i = 0; i < GRID_WIDTH; ++i)
	{
		for (int j = 0; j < GRID_HEIGHT; ++j)
		{
			grid[i][j] = Block::empty;
		}
	}
}

void Game::Run()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error("SDL could not initialize!");
	}

	window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		throw std::runtime_error("Window could not be created!");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		throw std::runtime_error("Renderer could not be created!");
	}

	alive = true;
	running = true;
	ReplaceFood();
	GameLoop();
}

void Game::ReplaceFood()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> xDist(0, GRID_WIDTH - 1);
	std::uniform_int_distribution<int> yDist(0, GRID_HEIGHT - 1);

	while (true)
	{
		int x = xDist(gen);
		int y = yDist(gen);

		if (grid[x][y] == Block::empty)
		{
			grid[x][y] = Block::food;
			food.x = x;
			food.y = y;
			break;
		}
	}
}

void Game::GameLoop()
{
	Uint32 before, second = SDL_GetTicks(), after;
	int frame_time, frames = 0;

	while (running)
	{
		before = SDL_GetTicks();

		PollEvents();
		Update();
		Render();

		frames++;
		after = SDL_GetTicks();
		frame_time = after - before;

		if (after - second >= 1000)
		{
			fps = frames;
			frames = 0;
			second = after;
			UpdateWindowTitle();
		}

		if (FRAME_RATE > frame_time)
		{
			SDL_Delay(FRAME_RATE - frame_time);
		}
	}
}

void Game::PollEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running = false;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				if (last_dir != Move::down || size == 1)
					dir = Move::up;
				break;

			case SDLK_DOWN:
				if (last_dir != Move::up || size == 1)
					dir = Move::down;
				break;

			case SDLK_LEFT:
				if (last_dir != Move::right || size == 1)
					dir = Move::left;
				break;

			case SDLK_RIGHT:
				if (last_dir != Move::left || size == 1)
					dir = Move::right;
				break;
			}
		}
	}
}

int Game::GetSize()
{
	return size;
}

void Game::GrowBody(int quantity)
{
	growing += quantity;
}

void Game::Update()
{
	if (!alive)
		return;

	switch (dir)
	{
	case Move::up:
		pos.y -= speed;
		pos.x = floorf(pos.x);
		break;

	case Move::down:
		pos.y += speed;
		pos.x = floorf(pos.x);
		break;

	case Move::left:
		pos.x -= speed;
		pos.y = floorf(pos.y);
		break;

	case Move::right:
		pos.x += speed;
		pos.y = floorf(pos.y);
		break;
	}

	if (pos.x < 0)
		pos.x = GRID_WIDTH - 1;
	else if (pos.x > GRID_WIDTH - 1)
		pos.x = 0;

	if (pos.y < 0)
		pos.y = GRID_HEIGHT - 1;
	else if (pos.y > GRID_HEIGHT - 1)
		pos.y = 0;

	int new_x = static_cast<int>(pos.x);
	int new_y = static_cast<int>(pos.y);
	if (new_x != head.x || new_y != head.y)
	{
		last_dir = dir;

		if (growing > 0)
		{
			size++;
			body.push_back(head);
			growing--;
			grid[head.x][head.y] = Block::body;
		}
		else
		{
			SDL_Point free = head;
			std::vector<SDL_Point>::reverse_iterator rit = body.rbegin();
			for (; rit != body.rend(); ++rit)
			{
				grid[free.x][free.y] = Block::body;
				std::swap(*rit, free);
			}

			grid[free.x][free.y] = Block::empty;
		}
	}

	head.x = new_x;
	head.y = new_y;

	Block &next = grid[head.x][head.y];
	if (next == Block::food)
	{
		score++;
		ReplaceFood();
		GrowBody(1);
	}
	else if (next == Block::body)
	{
		alive = false;
	}

	next = Block::head;
}

int Game::GetScore()
{
	return score;
}

void Game::UpdateWindowTitle()
{
	std::string title = "CppSnake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps);
	SDL_SetWindowTitle(window, title.c_str());
}

void Game::Render()
{
	SDL_Rect block;
	block.w = SCREEN_WIDTH / GRID_WIDTH;
	block.h = SCREEN_WIDTH / GRID_HEIGHT;

	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
	SDL_RenderClear(renderer);

	// Render food
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x33, 0x00, 0xFF);
	block.x = food.x * block.w;
	block.y = food.y * block.h;
	SDL_RenderFillRect(renderer, &block);

	// Render snake's body
	SDL_SetRenderDrawColor(renderer, 0x80, 0xAE, 0xEC, 0xFF);
	for (SDL_Point &point : body)
	{
		block.x = point.x * block.w;
		block.y = point.y * block.h;
		SDL_RenderFillRect(renderer, &block);
	}

	// Render snake's head
	block.x = head.x * block.w;
	block.y = head.y * block.h;
	if (alive)
		SDL_SetRenderDrawColor(renderer, 0x00, 0x5C, 0xD8, 0xFF);
	else
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(renderer, &block);

	// Update Screen
	SDL_RenderPresent(renderer);
}

void Game::Close()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}
