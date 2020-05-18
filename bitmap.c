#include "chip8.h"

/*
char *debug_text = "";

SDL_Window *debug_window;
SDL_Renderer *debug_renderer;

SDL_Surface *surfaceMessage;

SDL_Texture *Message;

SDL_Rect Message_rect;

TTF_Font *Font;

SDL_Color White = {255, 255, 255};
SDL_Color Black = {0, 0, 0};
*/

void updateDisplay()
{
	SDL_RenderPresent(renderer);
}

bool setPixel(int x, int y)
{
	int location = x + (width * y);
	if (location > 2047)
	{
		printf("bad location: program tried to draw at location %d, %d", x, y);
		return true;
	}
	
	gfx[location] ^= true;
	
	return gfx[location];			// returns true if no collision
}

void setPixels()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int location = gfx[x + (width * y)];
			if (location)
			{
				for (int i = 0; i < scale; i++)
				{
					for (int j = 0; j < scale; j++)
					{
						SDL_RenderDrawPoint(renderer, x * scale + i, y * scale + j);
					}
				}
			}
		}
	}
	drawFlag = true;
}

/* broken debug code don't worry 'bout it
void initDebug()
{
	TTF_Init();
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	
	debug_window = SDL_CreateWindow("Debugger", 0, 0, 150, 500, 0);
	debug_renderer = SDL_CreateRenderer(debug_window, -1, SDL_RENDERER_ACCELERATED);
	
	Font = TTF_OpenFont("HelveticaNeue.ttc", 300);
	
	SDL_SetRenderDrawColor(debug_renderer, 255, 255, 255, 255);
	SDL_RenderClear(debug_renderer);
}

void debug()
{
	SDL_SetRenderDrawColor(debug_renderer, 255, 255, 255, 255);
	SDL_RenderClear(debug_renderer);
	
	for (int i = 0; i < VLEN; i++)
	{
		char *original = debug_text;
		char *buf = "V[%d]: 0x%X\n", i, V[i];
		char *putitalltogether = malloc(strlen(original) + strlen(buf) + 1);
		snprintf(putitalltogether, sizeof putitalltogether, "%s%s", original, buf);
		debug_text = putitalltogether;
	}
	
	SDL_SetRenderDrawColor(debug_renderer, 0, 0, 0, 0);
	
	surfaceMessage = TTF_RenderText_Solid(Font, debug_text, Black); // as TTF_RenderText_Solid can only be used on SDL_Surface, we have to create the surface first
	
	Message = SDL_CreateTextureFromSurface(debug_renderer, surfaceMessage); // now you can convert it into a texture
	
	Message_rect.x = 0;
	Message_rect.y = 0;
	Message_rect.w = 80;
	Message_rect.h = 18;
	
	// now since it's a texture, we have to put RenderCopy in our loop area, the area where the whole code executes
	SDL_RenderCopy(debug_renderer, Message, NULL, &Message_rect); // you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	
	// don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
	
	// also render your stuff
	SDL_RenderPresent(debug_renderer);
}
*/

void initGUI()
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = SDL_CreateWindow("Chip 8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		exit(1);
	}
	return;
}