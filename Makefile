all:
	gcc *.c -o chip8 $(shell sdl2-config --cflags --libs)
	chmod +x chip8

run:
	./chip8 tetris.ch8

clean:
	rm chip8 || continue