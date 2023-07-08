# snake-cpp

This is a simple Snake game implemented in C++. It features the classic gameplay of the Snake game, with some additional enhancements.

## Usage

To compile and run the Snake game, follow these steps:

1. Clone the repository: `git clone https://github.com/walker84837/snake-cpp.git`;

2. Navigate to the project directory: `cd snake-cpp`;

3. Compile the source code using CMake: `make`;

4. Run the game:`./snake`;

5. Use the arrow keys to control the snake. The goal is to eat the food and avoid collisions with the snake's body or the screen edges.

## Contributing

Contributions are welcome! If you would like to contribute to this project, please follow these steps:

1. Fork the repository.

2. Create a new branch for your feature or bug fix.

3. Make your changes and commit them to your branch.

4. Push your branch to your forked repository.

5. Submit a pull request detailing your changes and improvements.

## Known issues & missing features

- When closing the window by pressing the cross after losing, it seems to set the gameover state to false and let you keep playing, instead of closing the window and showing your final score and the snake's length.
  - More details: You can revive yourself only once, then you can't anymore. Because of this, you're forced to press CTRL+C in the terminal to close the window and make it show the final score and length.
  - *Sub-issue: The cross isn't reponsive anymore after you lose and revive yourself by closing the window*.

- There is no pause-resume button.

- There isn't a live score counter.

- The window can't be resized or shrinked.

- There is no settings menu to set frame rate limits or resolution.

- At a certain point (as of this writing, with a score of >=40), the apple will randomly switch positions without being eaten by the snake.

- **OPTIONAL**: Add a border for the snake body.

5. Submit a pull request detailing your changes and improvements.

## License

This project is licensed under the GPLv3 License. For more information, please see the [LICENSE](LICENSE) file.
