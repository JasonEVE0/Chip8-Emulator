#include "Emulator.h"

Emulator::Emulator() {
	this->memory = new Memory();
	this->display = new Display();
}

Emulator::~Emulator() {
	delete this->memory;
	delete this->display;
}

unsigned short Emulator::fetch() {
	return memory->fetchInstruction();
}

void Emulator::execute() {

}
