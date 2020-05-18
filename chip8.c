#include "chip8.h"

int main(int argc, char *argv[])
{
	initGUI();
	// initDebug();
	SDL_Event e;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		if (drawFlag)
		{
			updateDisplay();
		}
		
		// debug();
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}