#ifndef MEMORY_H
#define MEMORY_H

#include "Register.h"

class Memory
{
public:
	Memory();
	~Memory();
	void storeMemory(unsigned char* programMemory, int index, int size);
	unsigned char getMemoryCell(int index);
private:
	unsigned char* memory;
	unsigned char* font;
};

#endif