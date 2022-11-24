#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <vector>

class Display {
public:
	Display();
	~Display();
	void setPixel(int x, int y, bool onoff);
	bool isPixelSet(int x, int y);
private:
	bool screen[64][32];
};

#endif