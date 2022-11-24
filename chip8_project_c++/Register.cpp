#include "Register.h"

Register::Register() {
	this->PC = 512;
	this->I = 0;
	this->delayTimer = 0;
	this->soundTimer = 0;
	this->V = new unsigned char[16];

	for (int i = 0; i < 16; i++) {
		V[i] = 0;
	}
}

Register::~Register() {
	delete[] this->V;
}

unsigned short Register::fetchPC() {
	return this->PC;
}

void Register::incrementPC() {
	this->PC += 2;
}