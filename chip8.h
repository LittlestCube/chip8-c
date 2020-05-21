#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#include <time.h>
#include <errno.h>

// bitmap.c
#define width 64
#define height 32

#define scale 10

void initGUI();
bool setPixel(int x, int y);
void setPixels();
void updateDisplay();
void displayClear();
void debugRender();

unsigned char gfx[width * height];
SDL_Window *window;
SDL_Renderer *renderer;

// audio.c
void initAudio();

// cpu.c
#define VLEN 16			// 16 is also the length of the keys

#define MEMLEN 4096

void initCPU();
void msleep(long msec);
void cycle();

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

// key.c
void setKeyT(int index);
void setKeyF(int index);
void checkKeys(SDL_Event e);

bool keys[16];