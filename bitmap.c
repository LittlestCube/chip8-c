#include "chip8.h"

void updateDisplay()
{
	SDL_RenderPresent(renderer);
}

void initGUI()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("Chip 8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w * scale, h * scale, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		exit(1);
	}
	return;
}