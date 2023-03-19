# Snake

This program is a simple implementation of the classic Snake game using the SDL2 library in C++.

## How to play

- Use the arrow keys to change the direction of the snake's movement.
- The game is over if the snake collides with the wall or its own tail.
- The score is displayed on the top left corner of the screen.

## Prerequisites

To run this program, you need to have the SDL2 library installed on your system. You can download it from the official website:

- [SDL2](https://github.com/libsdl-org/SDL/releases/latest)

## Building and running

To build the program, run the following commands:

```g++ -o snake main.cpp sdl2-config --cflags --libs -lSDL2_ttf```

To run the program, execute the following command:

```./snake```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

