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