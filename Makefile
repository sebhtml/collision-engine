CXX = g++
CXXCLAGS = -Wall -std=c++98 -O3 
LDFLAGS = -lm -lSDL

all: game

game: Game.o main.o Object.o Wall.o Ball.o Screen.o Grid.o Vector.o
	$(CXX) Vector.o Screen.o Game.o main.o Object.o Wall.o Ball.o Grid.o -o game $(LDFLAGS)

Game.o: Game.cpp
	$(CXX) Game.cpp -c -o Game.o $(CXXCLAGS)

Vector.o: Vector.cpp
	$(CXX) Vector.cpp -c -o Vector.o $(CXXCLAGS)

main.o: main.cpp
	$(CXX) main.cpp -c -o main.o $(CXXCLAGS)

Wall.o: Wall.cpp
	$(CXX) Wall.cpp -c -o Wall.o $(CXXCLAGS)
Ball.o: Ball.cpp
	$(CXX) Ball.cpp -c -o Ball.o $(CXXCLAGS)

Object.o: Object.cpp
	$(CXX) Object.cpp -c -o Object.o $(CXXCLAGS)
Screen.o: Screen.cpp
	$(CXX) Screen.cpp -c -o Screen.o $(CXXCLAGS)
Grid.o: Grid.cpp
	$(CXX) Grid.cpp -c -o Grid.o $(CXXCLAGS)

clean:
	rm game *.o
