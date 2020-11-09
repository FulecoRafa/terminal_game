game: build
	g++ -fsanitize=address -o game src/bin/*.o io/bin/*.o main.cpp -lncurses

build: semaphore src io
	make -C semaphore
	make -C src
	make -C io
