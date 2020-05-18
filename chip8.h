#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define width 64
#define height 32

#define scale 16

#define VLEN 16

void initGUI();
bool setPixel();
void setPixels();
void updateDisplay();
// void initDebug();
// void debug();

SDL_Window *window;
SDL_Renderer *renderer;

// CPU stuffs
unsigned char memory[4096];

unsigned char V[VLEN];

unsigned short stack[16];

unsigned short pc;
unsigned short opcode;
unsigned short I;
unsigned short sp;

unsigned int delay_timer;
unsigned int sound_timer;

bool drawFlag;
bool gfx[width * height];