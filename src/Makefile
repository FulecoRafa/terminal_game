flags=-g -fsanitize=address

build: folders all

all: output.o character.o item.o map.o position.o
	g++ $(flags) main.cpp bin/*.o -o test/test

output.o: map.o character.o
	g++ $(flags) -c output.cpp -o bin/output.o

character.o: item.o map.o position.o
	g++ $(flags) -c character.cpp -o bin/character.o

item.o: position.o
	g++ $(flags) -c item.cpp -o bin/item.o

map.o: position.o
	g++ $(flags) -c map.cpp -o bin/map.o

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
