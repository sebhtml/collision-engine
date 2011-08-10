CXX = g++
CXXCLAGS = -Wall -std=c++98 -O3 
LDFLAGS = -lm -lSDL -lGL

all: game

OBJECTS=Game.o main.o Object.o Wall.o Ball.o Screen.o Grid.o Vector.o OctreeNode.o Octree.o OctreeAllocator.o

game: $(OBJECTS)
	$(CXX) $(OBJECTS) -o game $(LDFLAGS)

# inference rule
%.o: %.cpp
	$(CXX) -c -o $@ $<  $(CXXFLAGS)


clean:
	rm game *.o
