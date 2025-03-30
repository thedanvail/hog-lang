ROOT_DIR := $(shell pwd)

build:
	mkdir build
	cmake -S . -B build
	cmake --build build
	mv build/compile_commands.json .

clean:
	rm -rf build/

fresh:
	make clean && make build

test:
	./hogc test.hog

fresh-test:
	make clean && make test

