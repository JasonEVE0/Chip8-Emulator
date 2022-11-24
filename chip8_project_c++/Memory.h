#ifndef MEMORY_H
#define MEMORY_H

#include "Register.h"

class Memory
{
public:
	Memory();
	~Memory();
	unsigned short fetchInstruction();
private:
	Register* registers;
	unsigned char* memory;
	unsigned char* font;
};

#endif