CXX = g++
CXXFLAGS = -O4 -std=c++17
SDL_INCLUDE = -I/usr/include/SDL2
SDL_LIB = -lSDL2

SRC = main.cpp Game.cpp
EXECUTABLE = snake

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXECUTABLE) $(SDL_INCLUDE) $(SDL_LIB)

clean:
	rm -f $(EXECUTABLE)
