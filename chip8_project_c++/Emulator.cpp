#include "Emulator.h"
#include <memory>

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
	switch (instruction & 0xf000) {
		case 0x0000:
			display->clearScreen();
			break;
		case 0xd000:
			display->draw(instruction, memory);
			break;
		case 0x1000:
			jump(instruction);
			break;
		case 0x6000:
			memory->getRegisters()->setRegister(instruction);
			break;
		case 0x7000:
			memory->getRegisters()->addRegister(instruction);
			break;
		case 0xa000:
			memory->getRegisters()->setIndex(instruction);
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
	memory->getRegisters()->setPC(value);
}

