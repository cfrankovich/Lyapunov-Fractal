CC = g++
CFLAGS =
LDFLAGS =
NAME = lfg

all: create
	@echo "Compile success."

create: ComputeFractal.o
	$(CC) $(CFLAGS) ComputeFractal.o -o $(NAME) $(LDFLAGS)

ComputeFractal.o: ComputeFractal.cpp
	$(CC) $(CFLAGS) -o $@ -c $^ $(LDFLAGS)
