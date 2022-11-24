#include "Display.h"

#include <vector>

Display::Display() {
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 32; j++) {
			screen[i][j] = false;
		}
	}
}

Display::~Display() {
	delete[] screen;
}

void Display::setPixel(int x, int y, bool onoff) {
	screen[x][y] = onoff;
}



bool Display::isPixelSet(int x, int y) {
	return screen[x][y];
}
