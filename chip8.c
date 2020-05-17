#include "chip8.h"

int main(int argc, char *argv[])
{
	initGUI();
	SDL_Event e;
	bool quit = false;
	while (!quit){
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT){
				quit = true;
			}
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}