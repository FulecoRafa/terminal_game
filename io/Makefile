flags=-g -fsanitize=address

build: folders output.o input.o

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
