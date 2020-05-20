#include "chip8.h"

unsigned short pc = 0x200;

unsigned char tmp_chip8_fontset[] =
{ 
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

void initCPU()
{
	for (int i = 0; i < 80; i++)
	{
		memory[i] = tmp_chip8_fontset[i];
	}
}

void nextOp()
{
	pc += 2;	// add 2 to program counter (as opcodes are two bytes long)
}

void msleep(long millisec)
{
	struct timespec ts;
	
	ts.tv_sec = millisec / 1000;
	ts.tv_nsec = (millisec % 1000) * 1000000;
	
	nanosleep(&ts, &ts);
}

void cycle()
{
	if (pc <= 4095 && pc >= 0)
	{
		opcode = (short) ((memory[pc] << (short) 8) | memory[pc + 1]);
	}
	
	else
	{
		printf("\npc 0x%X out of bounds, closing...", pc);
		exit(1);
	}
	
	unsigned char VXaddr = ((opcode & 0x0F00) >> 8);
	unsigned char VYaddr = ((opcode & 0x00F0) >> 4);
	unsigned char N = (opcode & 0x000F);
	unsigned char NN = (opcode & 0x00FF);
	unsigned short NNN = (opcode & 0x0FFF);
	
	switch (opcode & 0xF000)
	{
		case 0x0000:
		{
			switch (opcode & 0x00FF)
			{
				case 0x00E0:	// 0x00E0: clears the screen
				{
					displayClear();
					
					nextOp();
					break;
				}
				
				case 0x00EE:	// 0x00EE: returns from a subroutine
				{
					--sp;
					pc = stack[sp];
					stack[sp] = 0;
					
					nextOp();
					break;
				}
			}
			break;
		}
		
		case 0x1000:			// 0x1NNN: jumps to address NNN
		{
			pc = NNN;
			break;
		}
		
		case 0x2000:			// 0x2NNN: calls subroutine at NNN
		{
			stack[sp] = pc;
			++sp;
			pc = NNN;
			break;
		}
		
		case 0x3000:			// 0x3XNN: skips the next instruction if VX equals NN
		{
			if (V[VXaddr] == NN)
			{
				nextOp();
			}
			
			nextOp();
			break;
		}
		
		case 0x4000:			// 0x4000: skips the next instruction if VX doesn't equal NN
		{
			if (V[VXaddr] != NN)
			{
				nextOp();
			}
			
			nextOp();
			break;
		}
		
		case 0x5000:			// 0x5XY0: skips the next instruction if VX equals VY
		{
			if (V[VXaddr] == V[VYaddr])
			{
				nextOp();
			}
			
			nextOp();
			break;
		}
		
		case 0x6000:			// 0x6XNN: sets VX to NN
		{
			V[VXaddr] = NN;
			
			nextOp();
			break;
		}
		
		case 0x7000:			// 0x7XNN: adds NN to VX
		{
			V[VXaddr] += NN;
			
			nextOp();
			break;
		}
		
		case 0x8000:
		{
			switch (opcode & 0x000F)
			{
				case 0x0000:	// 0x8XY0: sets VX to the value of VY
				{
					V[VXaddr] = V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0001:	// 0x8XY0: sets VX to VX | VY
				{
					V[VXaddr] |= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0002:	// 0x8XY2: sets VX to VX & VY
				{
					V[VXaddr] &= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0003:	// 0x8XY3: sets VX to VX ^ VY
				{
					V[VXaddr] ^= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0004:	// 0x8XY4: adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
				{
					if (V[VXaddr] + V[VYaddr] > 255)
					{
						V[0xF] = 1;
					}
					
					else
					{
						V[0xF] = 0;
					}
					
					V[VXaddr] += V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0005:	// 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
				{
					if (V[VYaddr] > V[VXaddr])
					{
						V[0xF] = 0;
					}
					
					else
					{
						V[0xF] = 1;
					}
					
					V[VXaddr] -= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0006:	// 0x8X?6: stores the least significant bit of VX in VF and then shifts VX to the right by 1
				{
					V[0xF] = V[VXaddr] & 0x01;
					
					V[VXaddr] >>= 1;
					
					nextOp();
					break;
				}
				
				case 0x0007:	// 0x8XY7: sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
				{
					if (V[VXaddr] > V[VYaddr])
					{
						V[0xF] = 0;
					}
					
					else
					{
						V[0xF] = 1;
					}
					
					V[VXaddr] = V[VYaddr] - V[VXaddr];
					
					nextOp();
					break;
				}
				
				case 0x000E:	// 0x8X?E: stores the most significant bit of VX in VF and then shifts VX to the left by 1
				{
					V[0xF] = (V[VXaddr] & 0x80) >> 7;
					
					V[VXaddr] <<= 1;
					
					nextOp();
					break;
				}
			}
			break;
		}
		
		case 0x9000:			// 0x9XY0: skips the next instruction if VX doesn't equal VY
		{
			if (V[VXaddr] != V[VYaddr])
			{
				nextOp();
			}
			
			nextOp();
			break;
		}
		
		case 0xA000:			// 0xANNN: sets I to the address NNN
		{
			I = NNN;
			
			nextOp();
			break;
		}
		
		case 0xB000:			// 0xBNNN: jumps to the address NNN plus V0
		{
			pc = NNN + V[0x0];
			break;
		}
		
		case 0xC000:			// 0xCNNN: sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN
		{
			int rand_num = rand() % 256;
			
			V[VXaddr] = rand_num & NN;
			
			nextOp();
			break;
		}
		
		case 0xD000:			// 0xDXYN: draws a sprite from memory[I] at (VX, VY) that has a width of 8 pixels and a height of N pixels. VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
		{
			V[0xF] = 0;
			
			for (int currLine = 0; currLine < N; currLine++)
			{
				for (int currPixel = 0; currPixel < 8; currPixel++)
				{
					if ((memory[I + currLine] & (0x80 >> currPixel)) != 0)
					{
						bool collision = setPixel(V[VXaddr] + currPixel, V[VYaddr] + currLine);		// remember, this returns true if no collision
						
						if (!collision)
						{
							V[0xF] = 1;
						}
					}
				}
			}
			
			drawFlag = true;
			
			nextOp();
			break;
		}
		
		case 0xE000:
		{
			switch (opcode & 0x00FF)
			{
				case 0x009E:	// 0xEX9E: skips the next instruction if the key stored in VX is pressed
				{
					if (keys[V[VXaddr]])
					{
						nextOp();
					}
					
					nextOp();
					break;
				}
				
				case 0x00A1:	// 0xEXA1: skips the next instruction if the key stored in VX isn't pressed
				{
					if (!keys[V[VXaddr]])
					{
						nextOp();
					}
					
					nextOp();
					break;
				}
			}
			break;
		}
		
		case 0xF000:
		{
			switch (opcode & 0x00FF)
			{
				case 0x0007:	// 0xFX07: sets VX to the value of the delay timer
				{
					V[VXaddr] = delay_timer;
					
					nextOp();
					break;
				}
				
				case 0x000A:	// 0xFX0A: a key press is awaited, and then stored in VX
				{
					for (int i = 0; i < VLEN; i++)
					{
						if (keys[i])
						{
							V[VXaddr] = i;
							
							nextOp();
						}
					}
					
					break;
				}
				
				case 0x0015:	// 0xFX15: sets the delay timer to VX
				{
					delay_timer = V[VXaddr];
					
					nextOp();
					break;
				}
				
				case 0x0018:	// 0xFX18: sets the sound timer to VX
				{
					sound_timer = V[VXaddr];
					
					nextOp();
					break;
				}
				
				case 0x001E:	// 0xFX1E: adds VX to I. VF is set to 1 when there is a range overflow (I+VX>0xFFF), and to 0 when there isn't
				{
					if ((I + V[VXaddr]) > 0x0FFF)
					{
						V[0xF] = 1;
					}
					
					else
					{
						V[0xF] = 0;
					}
					
					I += V[VXaddr];
					
					nextOp();
					break;
				}
				
				case 0x0029:	// 0xFX29: sets I to the location of the sprite for the character in VX
				{
					I = V[VXaddr] * 0x5;
					
					nextOp();
					break;
				}
				
				case 0x0033:	// 0xFX33: stores the binary-coded decimal representation of VX in memory[I]
				{
					unsigned char l_digit = V[VXaddr] / 100;
					unsigned char m_digit = (V[VXaddr] / 10) % 10;
					unsigned char r_digit = (V[VXaddr] % 100) % 10;
					
					memory[I] = l_digit;
					memory[I + 1] = m_digit;
					memory[I + 2] = r_digit;
					
					nextOp();
					break;
				}
				
				case 0x0055:	// 0xFX55: stores V0 to VX (including VX) in memory starting at address I. I itself is left unmodified
				{
					for (int i = 0; i <= VXaddr; i++)
					{
						memory[I + i] = V[i];
					}
					
					nextOp();
					break;
				}
				
				case 0x0065:	// 0xFX65: fills V0 to VX (including VX) with values from memory starting at address I. I itself is left unmodified
				{
					for (int i = 0; i <= VXaddr; i++)
					{
						V[i] = memory[I + i];
					}
					
					nextOp();
					break;
				}
			}
			break;
		}
	}
	
	if (delay_timer > 0)
	{
		delay_timer--;
		msleep(12);
	}
	
	if (sound_timer > 0)
	{
		if (sound_timer == 1)
		{
			printf("BEEP!");
		}
		
		sound_timer--;
	}
}