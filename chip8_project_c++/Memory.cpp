#include "Memory.h"
#include <memory.h>

Memory::Memory() {
	this->registers = new Register();
	this->memory = new unsigned char[4096];
	for (int i = 0; i < 4096; i++) {
		memory[i] = 0;
	}

	font = new unsigned char[80] {
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};

	memcpy(&memory[0], font, 80);
}

Memory::~Memory() {
	delete[] this->memory;
	delete[] this->font;
}

/*
 * Fetches the 16 bit instruciton from memory,
 * and increments the PC
 */
unsigned short Memory::fetchInstruction() {
	unsigned short instruction = memory[registers->fetchPC()] << 8 | memory[registers->fetchPC() + 1];

	if (instruction != 0) {
		registers->incrementPC();
	}

	return instruction;
}

unsigned char* Memory::getMemory(int index) {
	return &this->memory[index];
}