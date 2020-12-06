flags=-g -fsanitize=address -std=c++11

build: folders semaphore

semaphore: fulecoSimpleSemaphore.o
	g++ $(flags) src/semTest.cpp bin/$^ -o test/sem

fulecoSimpleSemaphore.o:
	g++ $(flags) -c src/fulecoSimpleSemaphore.cpp -o bin/$@

folders:
	[ -d test ] || mkdir test
	[ -d bin ] || mkdir bin

clean:
	@rm -rf bin
	@rm -rf test
