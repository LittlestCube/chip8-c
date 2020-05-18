#include "chip8.h"

int main(int argc, char *argv[])
{
	initGUI();
	initCPU();
	SDL_Event e;
	bool quit = false;
	
	setPixel(31, 15);
	setPixel(0, 0);
	setPixel(63, 31);
	setPixels();
	
	memory[pc] = 0x00;
	memory[pc + 1] = 0xE0;
	
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
				{
					quit = true;
				}
				
				// look for a key press
				case SDL_KEYDOWN:
				{
					// check the SDLKey values and do stuff
					switch (e.key.keysym.sym)
					{
						case SDLK_1:
						{
							setKeyT(0x1);
							break;
						}
						
						case SDLK_2:
						{
							setKeyT(0x2);
							break;
						}
						
						case SDLK_3:
						{
							setKeyT(0x3);
							break;
						}
						
						case SDLK_q:
						{
							setKeyT(0x4);
							break;
						}
						
						case SDLK_w:
						{
							setKeyT(0x5);
							break;
						}
						
						case SDLK_e:
						{
							setKeyT(0x6);
							break;
						}
						
						case SDLK_a:
						{
							setKeyT(0x7);
							break;
						}
						
						case SDLK_s:
						{
							setKeyT(0x8);
							break;
						}
						
						case SDLK_d:
						{
							setKeyT(0x9);
							break;
						}
						
						case SDLK_x:
						{
							setKeyT(0x0);
							break;
						}
						
						case SDLK_z:
						{
							setKeyT(0xA);
							break;
						}
						
						case SDLK_c:
						{
							setKeyT(0xB);
							break;
						}
						
						case SDLK_4:
						{
							setKeyT(0xC);
							break;
						}
						
						case SDLK_r:
						{
							setKeyT(0xD);
							break;
						}
						
						case SDLK_f:
						{
							setKeyT(0xE);
							break;
						}
						
						case SDLK_v:
						{
							setKeyT(0xF);
							break;
						}
						
						default:
						{
							break;
						}
					}
				}
				
				// look for a key release
				case SDL_KEYUP:
				{
					// check the SDLKey values and do stuff
					switch (e.key.keysym.sym)
					{
						case SDLK_1:
						{
							setKeyF(0x1);
							break;
						}
						
						case SDLK_2:
						{
							setKeyF(0x2);
							break;
						}
						
						case SDLK_3:
						{
							setKeyF(0x3);
							break;
						}
						
						case SDLK_q:
						{
							setKeyF(0x4);
							break;
						}
						
						case SDLK_w:
						{
							setKeyF(0x5);
							break;
						}
						
						case SDLK_e:
						{
							setKeyF(0x6);
							break;
						}
						
						case SDLK_a:
						{
							setKeyF(0x7);
							break;
						}
						
						case SDLK_s:
						{
							setKeyF(0x8);
							break;
						}
						
						case SDLK_d:
						{
							setKeyF(0x9);
							break;
						}
						
						case SDLK_x:
						{
							setKeyF(0x0);
							break;
						}
						
						case SDLK_z:
						{
							setKeyF(0xA);
							break;
						}
						
						case SDLK_c:
						{
							setKeyF(0xB);
							break;
						}
						
						case SDLK_4:
						{
							setKeyF(0xC);
							break;
						}
						
						case SDLK_r:
						{
							setKeyF(0xD);
							break;
						}
						
						case SDLK_f:
						{
							setKeyF(0xE);
							break;
						}
						
						case SDLK_v:
						{
							setKeyF(0xF);
							break;
						}
						
						default:
						{
							break;
						}
					}
				}
				
				default:
				{
					break;
				}
			}
		}
		
		msleep(166);	// run at 60Hz (apporoximately)
		
		cycle();
		
		if (drawFlag)
		{
			updateDisplay();
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}