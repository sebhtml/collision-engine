CXX = g++
CXXFLAGS = -Wall -std=c++98 -DASSERT -O3
LDFLAGS = -lm -lSDL -lGL -lGLU

all: game

OBJECTS=Game.o main.o Object.o Wall.o Ball.o Screen.o Vector.o OctreeNode.o Octree.o OctreeAllocator.o

game: $(OBJECTS)
	$(CXX) $(OBJECTS) -o game $(LDFLAGS)

# inference rule
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< 


clean:
	rm game *.o
