all:
	gcc chip8.c bitmap.c -o chip8 -I/usr/local/include/SDL -D_GNU_SOURCE=1 -D_THREAD_SAFE -L/usr/local/lib -lSDL2main -lSDL2 -Wl,-framework,Cocoa
	chmod +x chip8

run:
	./chip8

clean:
	rm chip8 || continue