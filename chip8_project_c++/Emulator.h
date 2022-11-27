#ifndef EMULATOR_H
#define EMULATOR_H

#include "Memory.h"
#include "Display.h"
#include "Register.h"
#include "Keyboard.h"

class Emulator
{
public:
	Emulator();
	~Emulator();
	unsigned short fetch();
	void execute(unsigned short instruction);
	void storeMemory(unsigned char* memory, int index, int size);
	bool isPixelOn(int x, int y);
	char convertKey(char key);

private:
	void jump(unsigned short opcode);
	void returnFromSubroutine();
	void jumpSubroutine(unsigned short opcode);
	void skip(unsigned short opcode);
	Memory* memory;
	Register* registers;
	Display* display;
	Keyboard* keyboard;
};

#endif