build:
	gcc -Wall -std=c99 src/*.c -Isrc/headers -lSDL2 -o out

run:
	./out

clean:
	rm out