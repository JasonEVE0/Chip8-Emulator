#include "Emulator.h"
#include <iostream>

Emulator::Emulator() {
	this->memory = new Memory();
	this->display = new Display();
	this->registers = new Register();
}

Emulator::~Emulator() {
	delete this->memory;
	delete this->display;
	delete this->registers;
}

/*
 * Fetches the 16 bit instruciton from memory,
 * and increments the PC
 */
unsigned short Emulator::fetch() {
	unsigned short instruction = (memory->getMemoryCell(registers->fetchPC()) << 8) | memory->getMemoryCell(registers->fetchPC() + 1);

	if (instruction != 0) {
		registers->incrementPC();
	}

	return instruction;
}

// Decode and execute the instruction
void Emulator::execute(unsigned short instruction) {
	switch (instruction & 0xf000) {
		case 0x0000:
			display->clearScreen();
			break;
		case 0xd000:
			display->draw(instruction, registers, memory);
			break;
		case 0x1000:
			jump(instruction);
			break;
		case 0x6000:
			registers->setRegister(instruction);
			break;
		case 0x7000:
			registers->addRegister(instruction);
			break;
		case 0xa000:
			registers->setIndex(instruction);
			break;
		default:
			printf("unknown instruction: %x\n", instruction);
	}
}

void Emulator::storeMemory(unsigned char* destinationMemory, int index, int size) {
	this->memory->storeMemory(destinationMemory, index, size);
}

bool Emulator::isPixelOn(int x, int y) {
	return this->display->isPixelSet(x, y);
}

void Emulator::jump(unsigned short opcode) {
	unsigned short value = (opcode) & 0x0fff;
	registers->setPC(value);
}

