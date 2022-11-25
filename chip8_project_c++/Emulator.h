#ifndef EMULATOR_H
#define EMULATOR_H

#include "Memory.h"
#include "Display.h"
#include "Register.h"

class Emulator
{
public:
	Emulator();
	~Emulator();
	unsigned short fetch();
	void execute(unsigned short instruction);
	void storeMemory(unsigned char* memory, int index, int size);
	bool isPixelOn(int x, int y);
	void jump(unsigned short opcode);
private:
	Memory *memory;
	Display *display;
};

#endif