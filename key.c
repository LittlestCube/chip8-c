#include "chip8.h"

void setKey(int index, bool value)
{
	keys[index] = value;
}

void setKeyT(int index)
{
	setKey(index, true);
}

void setKeyF(int index)
{
	setKey(index, false);
}

void checkKeys(SDL_Event e)
{
	switch (e.type)
	{
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
				
				case SDLK_ESCAPE:
				{
					exit(0);
				}
				
				default:
				{
					break;
				}
			}
			break;
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
			break;
		}
	}
}