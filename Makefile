# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -Wshadow -std=c++11 -g

# SDL2 flags (includes and libraries)
SDL2_CFLAGS = `sdl2-config --cflags`
SDL2_LIBS = `sdl2-config --libs`
LDFLAGS = -lSDL2_ttf 

BUILDDIR = build
SRCDIR = src

# The source and target files
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
EXEC = sdltuts 

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(BUILDDIR)/$(EXEC) $(SDL2_LIBS) $(LDFLAGS)

# Compiling the object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(BUILDDIR)/$(EXEC)

# Clean up
clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(EXEC)

