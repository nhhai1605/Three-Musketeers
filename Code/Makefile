.default: all

all: azul

clean:
	rm -f azul *.o

azul : main.o Game.o Factories.o Mosaic.o LinkedList.o Tile.o TileBag.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^