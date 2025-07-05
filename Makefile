build:
	mkdir -p build
	gcc -Wall -std=c99 src/*.c -Isrc/headers -lSDL2 -o build/out
	

run:
	./build/out

clean:
	rm -rf build

.PHONY: build run clean