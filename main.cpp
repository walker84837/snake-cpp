#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

// Constants
const int WIDTH = 800;
const int HEIGHT = 600;
const int BLOCK_SIZE = 20;
const int FPS = 13;

// Colors
const SDL_Color BLACK = {22, 22, 22};
const SDL_Color WHITE = {255, 255, 255};
const SDL_Color GREEN = {0, 255, 0};
const SDL_Color RED = {255, 0, 0};
const SDL_Color BLUE = {0, 0, 255};

// Function prototypes
void drawText(SDL_Renderer* renderer, string text, int size, SDL_Color color, int x, int y);
void drawSnake(SDL_Renderer* renderer, vector<pair<int, int>>& snakeList);
bool checkCollision(vector<pair<int, int>>& snakeList, int headX, int headY);

// Main function
int main(int argc, char* argv[]) {
	// Initialization
	srand(time(NULL));
	SDL_Init(SDL_INIT_EVERYTHING);

	// Window and renderer
	SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Font
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(nullptr, 30);

	// Variables
	vector<pair<int, int>> snakeList{{WIDTH/2, HEIGHT/2}};
	int snakeLength = 1;
	int snakeX = snakeList[0].first;
	int snakeY = snakeList[0].second;
	string direction = "right";
	int foodX = rand() % ((WIDTH/BLOCK_SIZE) - 1) * BLOCK_SIZE;
	int foodY = rand() % ((HEIGHT/BLOCK_SIZE) - 1) * BLOCK_SIZE;

	// Loop
	bool game_over = false;
	SDL_Event event;
	while (!game_over) {
		// Handle events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game_over = true;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT && direction != "right") {
					direction = "left";
				}
				if (event.key.keysym.sym == SDLK_RIGHT && direction != "left") {
					direction = "right";
				}
				if (event.key.keysym.sym == SDLK_UP && direction != "down") {
					direction = "up";
				}
				if (event.key.keysym.sym == SDLK_DOWN && direction != "up") {
					direction = "down";
				}
			}
		}

		// Update snake
		if (direction == "left") {
			snakeX -= BLOCK_SIZE;
		} else if (direction == "right") {
			snakeX += BLOCK_SIZE;
		} else if (direction == "up") {
			snakeY -= BLOCK_SIZE;
		} else if (direction == "down") {
			snakeY += BLOCK_SIZE;
		}
		snakeList.push_back(make_pair(snakeX, snakeY));
		if (snakeList.size() > snakeLength) {
			snakeList.erase(snakeList.begin());
		}

		// Check for collision
		if (checkCollision(snakeList, snakeX, snakeY)) {
			game_over = true;
		}

		// Check if food has been eaten
		if (foodX == snakeX && foodY == snakeY) {
			snakeLength++;
			foodX = rand() % ((WIDTH/BLOCK_SIZE) - 1) * BLOCK_SIZE;
			foodY = rand() % ((HEIGHT/BLOCK_SIZE) - 1) * BLOCK_SIZE;
		}

		// Clear screen
		SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, 255);
		SDL_RenderClear(renderer);

		// Draw food
		SDL_Rect foodRect = {foodX, foodY, BLOCK_SIZE, BLOCK_SIZE};
		SDL_SetRenderDrawColor(renderer, RED.r, RED.g, RED.b, 255);
		SDL_RenderFillRect(renderer, &foodRect);

		// Draw snake
		drawSnake(renderer, snakeList);

		// Draw score
		string score = "Score: " + to_string(snakeLength - 1);
		drawText(renderer, score, 20, WHITE, 10, 10);

		// Update screen
		SDL_RenderPresent(renderer);

		// Delay
		SDL_Delay(1000/FPS);
	}

	// Cleanup
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

	// Draw text on the screen
	void drawText(SDL_Renderer* renderer, string text, int size, SDL_Color color, int x, int y) {
		TTF_Font* font = TTF_OpenFont(nullptr, size);
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		int texW = 0;
		int texH = 0;
		SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		SDL_Rect dstrect = { x, y, texW, texH };
		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
		TTF_CloseFont(font);
	}

// Draw the snake
	void drawSnake(SDL_Renderer* renderer, vector<pair<int, int>>& snakeList) {
		for (auto& p : snakeList) {
		SDL_Rect rect = {p.first, p.second, BLOCK_SIZE, BLOCK_SIZE};
		SDL_SetRenderDrawColor(renderer, GREEN.r, GREEN.g, GREEN.b, 255);
		SDL_RenderFillRect(renderer, &rect);
		}
	}

// Check if the snake has collided with itself or the boundaries
	bool checkCollision(vector<pair<int, int>>& snakeList, int headX, int headY) {
		// Check if the snake has collided with itself
		for (int i = 0; i < snakeList.size()-1; i++) {
			if (snakeList[i].first == headX && snakeList[i].second == headY) {
			return true;
			}
		}
	}   

	// Check if the snake has collided with the boundaries
	if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
		return true;
	}

	return false;
}