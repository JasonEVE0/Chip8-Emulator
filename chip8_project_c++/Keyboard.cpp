#include "Keyboard.h"

char Keyboard::convertRealToVirtual(char realKey) {
	switch (realKey) {
	case '1':
		return '1';
	case '2':
		return '2';
	case '3':
		return '3';
	case '4':
		return 'c';
	case 'q':
		return '4';
	case 'w':
		return '5';
	case 'e':
		return '6';
	case 'r':
		return 'd';
	case 'a':
		return '7';
	case 's':
		return '8';
	case 'd':
		return '9';
	case 'f':
		return 'e';
	case 'z':
		return 'a';
	case 'x':
		return '0';
	case 'c':
		return 'b';
	case 'v':
		return 'f';
	default:
		return 'x';
	}
}

void Keyboard::pressKey(char virtualKey) {
	hashmap[virtualKey] = true;
}

void Keyboard::releaseKey(char virtualKey) {
	hashmap[virtualKey] = false;
}

bool Keyboard::isPressed(char virtualKey) {
	if (hashmap.find(virtualKey) != hashmap.end()) {
		return hashmap[virtualKey];
	}
	return false;
}

// EX9E, EXA1 - Skip key
void Keyboard::skipKey(Register *registers, unsigned short opcode) {
	unsigned short trailing = opcode & 0xff;
	unsigned short x = (opcode >> 8) & 0xf;
	bool isKeyPressed = isPressed(registers->getV(x));

	if (trailing == 0x9E && isKeyPressed) {
		registers->incrementPC();
	}
	else if (trailing == 0xA1 && !isKeyPressed) {
		registers->incrementPC();
	}
}

