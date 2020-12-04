game: build
	g++ -g -fsanitize=address -o game semaphore/bin/fulecoSimpleSemaphore.o src/bin/*.o io/bin/*.o main.cpp -lncurses

build: semaphore src io
	make -C semaphore
	make -C src
	make -C io
