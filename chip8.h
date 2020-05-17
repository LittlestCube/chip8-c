#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define w 64
#define h 32

#define scale 16

void initGUI();

SDL_Window *window;
SDL_Renderer *renderer;

extern unsigned char gfx[w * h];