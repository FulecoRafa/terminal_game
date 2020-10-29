flags=-g -fsanitize=address

test:
	./test

all: output.o character.o item.o map.o position.o
	g++ $(flags) main.cpp $^ -o test

output.o: map.o character.o
	g++ $(flags) -c output.cpp -o output.o

character.o: item.o map.o position.o
	g++ $(flags) -c character.cpp -o character.o

item.o: position.o
	g++ $(flags) -c item.cpp -o item.o

map.o: position.o
	g++ $(flags) -c map.cpp -o map.o

position.o:
	g++ $(flags) -c position.cpp -o position.o

semaphore: fulecoSimpleSemaphore.o
	g++ $(flags) semTest.cpp $^ -o sem

fulecoSimpleSemaphore.o:
	g++ $(flags) -c fulecoSimpleSemaphore.cpp -o $@

clean:
	@rm -rf *.o
	@rm -rf test
	@rm -rf sem