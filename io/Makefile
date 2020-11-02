flags=-g -fsanitize=address

build: folders menu

menu: output.o
	g++ $(flags) src/test.cpp bin/$^ -o test/menu -lncurses

output.o:
	g++ $(flags) -c src/output.cpp -o bin/$@ -lncurses

folders:
	[ -d test ] || mkdir test
	[ -d bin ] || mkdir bin

clean:
	@rm -rf bin
	@rm -rf test
