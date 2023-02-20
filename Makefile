CC = g++
CFLAGS = -Wall -Wextra 

SDL_LIB = -L/opt/homebrew/lib
SDL_INCLUDE = -I/opt/homebrew/include/SDL2
SDL_CFLAGS = $(shell pkg-config --cflags sdl2)
override CFLAGS += $(SDL_CFLAGS)

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.cpp) 
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)) 
EXEC = LyapunovFractalRenderer


all: $(BIN_DIR)/$(EXEC)

$(BIN_DIR)/$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SDL_LIB) -lSDL2 $(OBJS) -o $(BIN_DIR)/$(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(SDL_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(EXEC)