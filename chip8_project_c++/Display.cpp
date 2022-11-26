#include "Display.h"

Display::Display() {
	clearScreen();
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

// Clears the screen
void Display::clearScreen() {
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 32; y++) {
			screen[x][y] = false;
		}
	}
}

// Draw - DXYN
void Display::draw(unsigned short opcode, Register* registers, Memory* memory) {
	unsigned char x = (opcode >> 8) & 0xf; 
	unsigned char y = (opcode >> 4) & 0xf;
	unsigned char n = (opcode) & 0xf;

	int xCoordinate = registers->getV(x) % 64;
	int yCoordinate = registers->getV(y) % 32;
	registers->setV(0xf, 0);

	for (int i = 0; i < n; i++) {
		if (yCoordinate > 31) break;
		unsigned char sprite = memory->getMemoryCell(registers->getI() + i);
		for (int j = 7; j >= 0; j--) {

			if (xCoordinate > 63) break;

			bool bitOn = ((sprite >> j) & 0x1) == 1;
			bool pixelOn = isPixelSet(xCoordinate, yCoordinate);

			if (bitOn && pixelOn) {
				setPixel(xCoordinate, yCoordinate, false);
				registers->setV(0xf, 1);
			}
			else if (bitOn && !pixelOn) {
				setPixel(xCoordinate, yCoordinate, true);
			}
		
			xCoordinate++;
		}
		xCoordinate -= 8;
		yCoordinate++;
	}

}