ROOT_DIR := $(shell pwd)

build:
	mkdir build
	cmake -S . -B build
	cmake --build build
	mv build/compile_commands.json .
	mv build/hogc .

clean:
	rm -rf build/

fresh:
	make clean && make build

test:
	./hogc test.hog

fresh-test:
	make clean && make test

check:
	cppcheck --enable=all --inconclusive --std=c++23 -I include .

