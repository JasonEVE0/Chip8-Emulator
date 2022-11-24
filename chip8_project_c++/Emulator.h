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
	void execute();
private:
	Memory *memory;
	Display *display;
};

#endif