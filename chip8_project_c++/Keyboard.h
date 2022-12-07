#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_map>
#include "Register.h"

class Keyboard {
public:
	char convertRealToVirtual(char realKey);
	void pressKey(char virtualKey);
	void releaseKey(char virtualKey);
	bool isPressed(char virtualKey);
	void skipKey(Register *registers, unsigned short opcode);
	bool anyKeyPressed();
private:
	std::unordered_map<char, bool> hashmap;
};

#endif