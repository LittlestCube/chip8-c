#include "chip8.h"

void updateDisplay()
{
	SDL_RenderPresent(renderer);
}

void displayClear()
{
	for (int i = 0; i < width * height; i++)
	{
		gfx[i] = 0;
	}
	
	setPixels();
}

bool setPixel(int x, int y)
{
	int location = x + (width * y);
	if (location > 2047 || location < 0)
	{
		printf("bad location: program tried to draw at location %d, %d\n", x, y);
		return true;
	}
	
	gfx[location] ^= 255;					// toggles gfx[location] from 0 to 255 and vice versa
	
	return gfx[location] == 255;			// returns true if no collision
}

void setPixels()
{
	unsigned char color;
	
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			color = gfx[x + (width * y)];
			
			SDL_SetRenderDrawColor(renderer, color, color, color, color);
			
			for (int i = 0; i < scale; i++)
			{
				for (int j = 0; j < scale; j++)
				{
					SDL_RenderDrawPoint(renderer, x * scale + i, y * scale + j);
				}
			}
		}
	}
	
	updateDisplay();
}

void debugRender()
	{
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (gfx[(y * width) + x]) 
					printf("O");
				else 
					printf(" ");
			}
			printf("\n");
		}
	}

void initGUI()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("Chip 8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		exit(1);
	}
	return;
}