# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -Wall

# SDL flags
SDL_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

# Source files
SRC = Main.cpp Queen.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Output file
OUT = app

# Default target
all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ) $(SDL_FLAGS)

# Rule for generating object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(OUT)
