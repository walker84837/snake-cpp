# Changelog

## v0.0.1

- Initial release.

## v0.0.2

- Refactor and rewrite entire game.
- Added the following files:
  - `Makefile`
  - Basic game files:
    - `Game.cpp`
    - `Game.hpp`
    - `main.cpp`
- Changed the license to GPLv3.

## v0.0.3

- Add JSON configuration to change:
  - Resolution
  - Framerate limit
- Fixed:
  - Doing CTRL+C in the command line revives you once
  - Close button isn't responsive. Fixed by making the window borderless and letting the user input a key to quit the game.
