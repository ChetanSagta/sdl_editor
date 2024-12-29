# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Werror -pedantic -Wshadow -std=c++11

# SDL2 flags (includes and libraries)
SDL2_CFLAGS = `sdl2-config --cflags`
SDL2_LIBS = `sdl2-config --libs`
LDFLAGS = -lSDL2_ttf 
# The source and target files
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = sdltuts 

BUILDDIR = build
SRCDIR = src

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJ)
	$(CXX) $(BUILDDIR)/$(OBJ) -o $(BUILDDIR)/$(EXEC) $(SDL2_LIBS) $(LDFLAGS)

# Compiling the object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $(SRCDIR)/$< -o $(BUILDDIR)/$@

run: $(EXEC)
	./$(BUILDDIR)/$(EXEC)

# Clean up
clean:
	rm -f $(OBJ) $(EXEC)

