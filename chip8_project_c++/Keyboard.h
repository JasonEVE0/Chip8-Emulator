#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_map>

class Keyboard {
public:
	char convertRealToVirtual(char realKey);
	void pressKey(char virtualKey);
	void releaseKey(char virtualKey);
	bool isPressed(char virtualKey);
private:
	std::unordered_map<char, bool> hashmap;
};

#endif