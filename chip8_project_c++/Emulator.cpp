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
	switch ((instruction >> 12) & 0xf) {
		case 0x0:
			display->clearScreen();
			break;
		case 0xd:
			display->draw(instruction, memory);
			break;
		case 0x1:
			jump(instruction);
			break;
		case 0x6:
			memory->registers->setRegister(instruction);
			break;
		case 0x7:
			memory->registers->addRegister(instruction);
			break;
		case 0xa:
			memory->registers->setIndex(instruction);
			break;
		default:
			printf("unknown instruction: %x\n", instruction);
	}
}

void Emulator::storeMemory(unsigned char* memory, int index, int size) {
		memcpy(this->memory->getMemory(index), memory, size);
}

bool Emulator::isPixelOn(int x, int y) {
	return this->display->isPixelSet(x, y);
}

void Emulator::jump(unsigned short opcode) {
	unsigned short value = (opcode) & 0x0fff;
	memory->registers->PC = value + 2;
}

