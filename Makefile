ROOT_DIR := $(shell pwd)

build:
	g++ $(shell find $(ROOT_DIR/src) -o hogc

clean:
	rm hogc 

fresh:
	make clean && make build

test:
	hogc test.hog

fresh-test:
	make clean && make test

