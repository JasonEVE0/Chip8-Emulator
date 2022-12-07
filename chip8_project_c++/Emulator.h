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
	// instruction set
	void jump(unsigned short opcode);
	void returnFromSubroutine();
	void jumpSubroutine(unsigned short opcode);
	void skip(unsigned short opcode);
	void set(unsigned short opcode);
	void binaryOr(unsigned short opcode);
	void binaryAnd(unsigned short opcode);
	void binaryXor(unsigned short opcode);
	void carryAdd(unsigned short opcode);
	void subtract(unsigned short opcode);
	void shift(unsigned short opcode);
	void jumpWithOffset(unsigned short opcode);
	void random(unsigned short opcode);
	void timerModification(unsigned short opcode);
	void addToIndex(unsigned short opcode);
	void getKey(unsigned short opcode);
	void fontCharacter(unsigned short opcode);
	void decimalConversion(unsigned short opcode);
	void storeMemoryInstruction(unsigned short opcode);
	void loadMemoryInstruction(unsigned short opcode);
	Memory* memory;
	Register* registers;
	Display* display;
	Keyboard* keyboard;
};

#endif