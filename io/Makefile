flags=-g -fsanitize=address -std=c++11

build: folders output.o input.o

test: build
	g++ $(flags) ./src/test2.cpp ./bin/*.o ../semaphore/bin/fulecoSimpleSemaphore.o -o ./test/input -lncurses

output.o:
	g++ $(flags) -c src/output.cpp ../src/bin/*.o -o bin/$@

input.o:
	g++ $(flags) -c src/input.cpp ../semaphore/bin/fulecoSimpleSemaphore.o -o bin/$@

folders:
	[ -d test ] || mkdir test
	[ -d bin ] || mkdir bin

clean:
	@rm -rf bin
	@rm -rf test
