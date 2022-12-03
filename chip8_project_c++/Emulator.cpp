#include "Emulator.h"
#include <iostream>

Emulator::Emulator() {
	this->memory = new Memory();
	this->display = new Display();
	this->registers = new Register();
	this->keyboard = new Keyboard();
}

Emulator::~Emulator() {
	delete this->memory;
	delete this->display;
	delete this->registers;
	delete this->keyboard;
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
			if ((instruction & 0xff) == 0xee){
				returnFromSubroutine();
			}
			else if ((instruction & 0xff) == 0xe0) {
				display->clearScreen();
			}
			break;
		case 0xd000:
			display->draw(instruction, registers, memory);
			break;
		case 0x1000:
			jump(instruction);
			break;
		case 0x2000:
			jumpSubroutine(instruction);
			break;
		case 0x3000:
			skip(instruction);
			break;
		case 0x4000:
			skip(instruction);
			break;
		case 0x5000:
			skip(instruction);
			break;
		case 0x6000:
			registers->setRegister(instruction);
			break;
		case 0x7000:
			registers->addRegister(instruction);
			break;
		case 0x8000:
			if ((instruction & 0xf) == 0){
				set(instruction);
			} else if ((instruction & 0xf) == 1) {
				binaryOr(instruction);
			} else if ((instruction & 0xf) == 2) {
				binaryAnd(instruction);
			} else if ((instruction & 0xf) == 3) {
				binaryXor(instruction);
			} else if ((instruction & 0xf) == 4) {
				carryAdd(instruction);
			} else if ((instruction & 0xf) == 5 || (instruction & 0xf) == 7) {
				subtract(instruction);
			} else if ((instruction & 0xf) == 6 || (instruction & 0xf) == 0xe) {
				shift(instruction);
			}
			break;
		case 0x9000:
			skip(instruction);
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

char Emulator::convertKey(char key) {
	return keyboard->convertRealToVirtual(key);
}

// 00EE - Return from subroutine
void Emulator::returnFromSubroutine() {
	registers->setPC(memory->peek());
	memory->pop();
}

// 2NNN - Jump Subroutine
void Emulator::jumpSubroutine(unsigned short opcode) {
	unsigned short nnn = opcode & 0xfff;
	memory->push(registers->fetchPC());
	registers->setPC(nnn);
}

// 3XNN, 4XNN, 5XY0, 9XY0 - Skip
void Emulator::skip(unsigned short opcode) {
	unsigned short lead = (opcode >> 12) & 0xf;
	unsigned short x = (opcode >> 8) & 0xf;

	if (lead == 0x3 || lead == 0x4) {
		unsigned short nn = (opcode) & 0xff;
		if (registers->getV(x) == nn) {
			// skip instruction 3XNN
			return;
		}
		else {
			// skip instruction 4XNN
			return;
		}
	}
	else if (lead == 0x5 || lead == 0x9) {
		unsigned short y = (opcode >> 4) & 0xf;
		if (registers->getV(x) == registers->getV(y)) {
			// skip instruction 5XY0
			return;
		}
		else {
			// skip instruction 9XY0
			return;
		}
	}
}

// 8XY0 - Set
void Emulator::set(unsigned short opcode) {
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;
	registers->setV(x, registers->getV(y));
}

// 8XY1 - Binary or
void Emulator::binaryOr(unsigned short opcode) {
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;
	registers->setV(x, (registers->getV(x) | registers->getV(y)));
}

// 8XY2 - Binary and
void Emulator::binaryAnd(unsigned short opcode) {
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;
	registers->setV(x, (registers->getV(x) & registers->getV(y)));
}

// 8XY3 - Binary xor
void Emulator::binaryXor(unsigned short opcode) {
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;
	registers->setV(x, (registers->getV(x) ^ registers->getV(y)));
}

// 8XY4 - Add with carry
void Emulator::carryAdd(unsigned short opcode) {
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;

	if (registers->getV(x) + registers->getV(y) > 255) {
		registers->setV(0xf, 1);
	}

	registers->setV(x, ((registers->getV(x) + registers->getV(y)) % 256));
}

// 8XY5 and 8XY7 - Subtract
void Emulator::subtract(unsigned short opcode) {
	unsigned short trailing = (opcode & 0xf);
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;

	if (trailing == 5) {
		if (registers->getV(x) > registers->getV(y)) {
			registers->setV(0xf, 1);
		}
		else if (registers->getV(x) < registers->getV(y)
			&& registers->getV(x) - registers->getV(y) < 0) {
			registers->setV(0xf, 0);
		}
		registers->setV(x, ((registers->getV(x) - registers->getV(y)) % 256));
	}
	else if (trailing == 7) {
		if (registers->getV(y) > registers->getV(x)) {
			registers->setV(0xf, 1);
		}
		else if (registers->getV(y) < registers->getV(x)
			&& registers->getV(y) - registers->getV(x) < 0) {
			registers->setV(0xf, 0);
		}
		registers->setV(x, ((registers->getV(y) - registers->getV(x)) % 256));
	}
}

void Emulator::shift(unsigned short opcode) {
	unsigned short trailing = opcode & 0xf;
	unsigned short x = (opcode >> 8) & 0xf;
	unsigned short y = (opcode >> 4) & 0xf;
	int bitShift = 0;

	registers->setV(x, registers->getV(y));

	if (trailing == 0x6) {
		bitShift = (registers->getV(x) & 0x1);
		registers->setV(x, (registers->getV(x) >> 1));
	} else if (trailing == 0xe) {
		registers->setV(x, (registers->getV(x) << 1));
	}

	if (bitShift == 0) {
		registers->setV(0xf, 0);
	} else if (bitShift == 1) {
		registers->setV(0xf, 1);
	}
}

