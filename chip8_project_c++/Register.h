#ifndef REGISTER_H
#define REGISTER_H

class Register {
public:
	Register();
	~Register();
	unsigned short fetchPC();
	void incrementPC();
	void setRegister(unsigned short opcode);
	void addRegister(unsigned short opcode);
	void setIndex(unsigned short opcode);
	void setPC(unsigned short counter);
	void setV(unsigned char index, unsigned char value);
	unsigned char getV(unsigned char index);
	unsigned short getI();
private:
	unsigned short PC;
	unsigned short I;
	unsigned char soundTimer;
	unsigned char delayTimer;
	unsigned char* V;
};

#endif