CC = g++
CFLAGS = -Wall -Wextra 

SDL_LIB = -L/opt/homebrew/lib
SDL_INCLUDE = -I/opt/homebrew/include/SDL2
SDL_CFLAGS = $(shell pkg-config --cflags sdl2)
override CFLAGS += $(SDL_CFLAGS)

SRCS = ComputeFractal.cpp
EXEC = LyapunovFractalRenderer

OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_LIB) -lSDL2 $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)