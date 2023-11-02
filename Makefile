CXX = g++
CXXFLAGS = -Ofast -std=gnu++17 -Wall -Wextra -pedantic
SDL_INCLUDE = -I/usr/include/SDL2
SDL_LIB = -lSDL2

BIN = bin
SRC = src/main.cpp src/Game.cpp 
EXECUTABLE = $(BIN)/snake

all: $(EXECUTABLE)

$(EXECUTABLE):
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXECUTABLE) $(SDL_INCLUDE) $(SDL_LIB)

clean:
	rm -rf $(BIN)
