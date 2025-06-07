default_target: build

build:
	if [ ! -d build ]; then \
		echo "Creating build directory." && mkdir build; \
	fi
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
	make clean && make build && make test

