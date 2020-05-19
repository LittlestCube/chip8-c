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
	unsigned char NN = (opcode & 0x00FF);
	unsigned short NNN = (opcode & 0x0FFF);
	
	printf("opcode: 0x%X\t\tpc: 0x%X\n", opcode, pc);
	
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
				case 0x0000:			// 0x8XY0: sets VX to the value of VY
				{
					V[VXaddr] = V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0001:			// 0x8XY0: sets VX to VX | VY
				{
					V[VXaddr] |= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0002:			// 0x8XY2: sets VX to VX & VY
				{
					V[VXaddr] &= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0003:			// 0x8XY3: sets VX to VX ^ VY
				{
					V[VXaddr] ^= V[VYaddr];
					
					nextOp();
					break;
				}
				
				case 0x0004:			// 0x8XY4: adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
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
				
				case 0x0005:			// 0x8XY5: VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
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
				
				case 0x0006:			// 0x8X?6: stores the least significant bit of VX in VF and then shifts VX to the right by 1
				{
					V[0xF] = V[VXaddr] & 0x01;
					
					V[VXaddr] >>= 1;
					
					nextOp();
					break;
				}
				
				case 0x0007:			// 0x8XY7: sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
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
				
				case 0x0008:			// 0x8X?8: stores the most significant bit of VX in VF and then shifts VX to the left by 1
				{
					V[0xF] = (V[VXaddr] & 0x80) >> 7;
					
					V[VXaddr] <<= 1;
					
					nextOp();
					break;
				}
			}
			break;
		}
	}
}