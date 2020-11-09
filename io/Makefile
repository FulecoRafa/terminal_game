flags=-g -fsanitize=address

build: folders output.o

output.o:
	g++ $(flags) -c src/output.cpp ../src/bin/*.o -o bin/$@

folders:
	[ -d test ] || mkdir test
	[ -d bin ] || mkdir bin

clean:
	@rm -rf bin
	@rm -rf test
