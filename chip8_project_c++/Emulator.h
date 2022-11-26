#ifndef EMULATOR_H
#define EMULATOR_H

#include "Memory.h"
#include "Display.h"

class Emulator
{
public:
	Emulator();
	~Emulator();
	unsigned short fetch();
	void execute(unsigned short instruction);
	void storeMemory(unsigned char* memory, int index, int size);
	bool isPixelOn(int x, int y);
private:
	void jump(unsigned short opcode);
	Memory *memory;
	Display *display;
};

#endif