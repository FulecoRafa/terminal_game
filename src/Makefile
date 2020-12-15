flags=-g -fsanitize=address -std=c++11

build: folders all

all: character.o item.o map.o position.o
	g++ $(flags) main.cpp bin/*.o ../semaphore/bin/fulecoSimpleSemaphore.o -o test/test

character.o: item.o map.o position.o
	g++ $(flags) -c character.cpp ../semaphore/bin/fulecoSimpleSemaphore.o -o bin/character.o

item.o: position.o
	g++ $(flags) -c item.cpp -o bin/item.o

map.o: position.o
	g++ $(flags) -c map.cpp ../semaphore/bin/fulecoSimpleSemaphore.o -o bin/map.o

position.o:
	g++ $(flags) -c position.cpp -o bin/position.o

folders:
	[ -d test ] || mkdir test
	[ -d bin ] || mkdir bin

test:
	./test

clean:
	@rm -rf *.o
	@rm -rf test
	@rm -rf sem
