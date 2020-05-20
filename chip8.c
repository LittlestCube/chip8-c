#include "chip8.h"

void debug()
{
	printf("pc: 0x%X\ncurrent opcode: 0x%X\nstack[sp]: 0x%X\nsp: 0x%X\nI: 0x%X\ndelay timer: 0x%X\nsound timer: 0x%X\n", pc, opcode, stack[sp], sp, I, delay_timer, sound_timer);
	
	for (int i = 0; i < VLEN; i++)
	{
		printf("V%d: 0x%X\n", i, V[i]);
	}
	
	printf("\n");
}

void loadGame(char *file)
{
	FILE *fileptr;
	char *ROM;
	long filelen;
	
	fileptr = fopen(file, "rb");
	fseek(fileptr, 0, SEEK_END);
	filelen = ftell(fileptr);
	rewind(fileptr);
	
	ROM = (char *) malloc(filelen * sizeof(char));
	fread(ROM, filelen, 1, fileptr);
	fclose(fileptr);
	
	for (int i = 0; i < filelen; i++)
	{
		memory[0x200 + i] = ROM[i];
	}
}

int main(int argc, char *argv[])
{
	initGUI();
	initCPU();
	SDL_Event e;
	bool quit = false;
	
	if (argc > 1)
	{
		loadGame(argv[1]);
	}
	
	else
	{
		printf("E: no game loaded! closing...");
		exit(1);
	}
	
	/*memory[0x200	] = 0x60;
	memory[0x200 + 1] = 0x00;
	
	memory[0x200 + 2] = 0x61;
	memory[0x200 + 3] = 0xE0;
	
	memory[0x200 + 4] = 0xA2;
	memory[0x200 + 5] = 0x14;
	
	memory[0x200 + 6] = 0xF1;
	memory[0x200 + 7] = 0x55;
	
	memory[0x200 + 8] = 0x12;
	memory[0x200 + 9] = 0x14;
	
	memory[0x200 + 10] = 0xD0;
	memory[0x200 + 11] = 0x11;
	
	memory[0x200 + 12] = 0xF0;
	memory[0x200 + 13] = 0x15;
	
	memory[0x200 + 14] = 0xF0;
	memory[0x200 + 15] = 0x07;*/
	
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			checkKeys(e);
			
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		
		//debug();
		
		//debugRender();
		
		cycle();
		
		if (drawFlag)
		{
			setPixels();
			updateDisplay();
		}
	}
	
	SDL_DestroyWindow(window);
	SDL_Quit();
}