#include "Emulator.h"
#include <memory>

#include <iostream>

Emulator::Emulator() {
	this->memory = new Memory();
	this->display = new Display();
}

Emulator::~Emulator() {
	delete this->memory;
	delete this->display;
}

// fetch instruction from memory
unsigned short Emulator::fetch() {
	return memory->fetchInstruction();
}

// decode and execute instruction
void Emulator::execute(unsigned short instruction) {
	switch (instruction) {
		case 0x00E0:
			printf("0x00e0");
			break;
	}
}

void Emulator::storeMemory(unsigned char* memory, int index, int size) {
		memcpy(this->memory->getMemory(index), memory, size);
}

bool Emulator::isPixelOn(int x, int y) {
	return this->display->isPixelSet(x, y);
}