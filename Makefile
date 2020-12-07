flags=-g -fsanitize=address -std=c++11

game: build game.o
	g++ -std=c++11 -g -fsanitize=address -o game semaphore/bin/fulecoSimpleSemaphore.o src/bin/*.o io/bin/*.o game.o main.cpp -lncurses

clean:
	rm -rf game *.o
	make clean -C semaphore
	make clean -C src
	make clean -C io

game.o: build
	g++ $(flags) -c game.cpp semaphore/bin/*.o src/bin/*.o io/bin/*.o -o game.o

build: semaphore src io
	make -C semaphore
	make -C src
	make -C io
