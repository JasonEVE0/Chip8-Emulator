#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>
#include "Memory.h"

class Display {
public:
	Display();
	~Display();
	void setPixel(int x, int y, bool onoff);
	bool isPixelSet(int x, int y);
	void clearScreen();
	void draw(unsigned short opcode, Memory* memory);
private:
	bool screen[64][32];
};

#endif