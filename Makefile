# Compiler
CXX = g++

# Compilation flags
CXXFLAGS = -Wall -Wextra -Werror -Wfatal-errors -std=c++20

# Target executable
TARGET = game_of_life

# Source files
SRC = main.cpp GameOfLife.cpp

# Header files
HEADER = GameOfLife.h

# Build target
$(TARGET): $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)
	@echo "Cleaned build files."
