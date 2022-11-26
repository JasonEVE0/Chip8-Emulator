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

// Set - 6XNN
void Register::setRegister(unsigned short opcode) {
	unsigned char x = (opcode >> 8) & 0x0f;
	unsigned char nn = opcode & 0x00ff;
	V[x] = nn;
}

// Add - 7XNN
void Register::addRegister(unsigned short opcode) {
	unsigned char x = (opcode >> 8) & 0x0f;
	unsigned char nn = opcode & 0x00ff;
	V[x] += nn;
}

// Set Index - ANNN
void Register::setIndex(unsigned short opcode) {
	unsigned short nnn = opcode & 0x0fff;
	I = nnn;
}

void Register::setPC(unsigned short counter) {
	this->PC = counter;
}

void Register::setV(unsigned char index, unsigned char value) {
	this->V[index] = value;
}

unsigned char Register::getV(unsigned char index) {
	return this->V[index];
}

unsigned short Register::getI() {
	return this->I;
}