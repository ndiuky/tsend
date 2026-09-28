.PHONY: configure build clean run

PROJECT_NAME = tsend

configure:
	cmake -S . -B build

build:
	cmake --build build

run:
	./build/$(PROJECT_NAME)

debug:
	gdb ./build/$(PROJECT_NAME)

clean:
	rm -rf build
