all:
	gcc *.c -o chip8 -D_THREAD_SAFE -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2
	chmod +x chip8

run:
	./chip8

clean:
	rm chip8 || continue