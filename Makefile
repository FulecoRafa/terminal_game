game: build
	g++ -std=c++11 -g -fsanitize=address -o game semaphore/bin/fulecoSimpleSemaphore.o src/bin/*.o io/bin/*.o main.cpp -lncurses

clean:
	rm -rf game *.o
	make clean -C semaphore
	make clean -C src
	make clean -C io

build: semaphore src io
	make -C semaphore
	make -C src
	make -C io
