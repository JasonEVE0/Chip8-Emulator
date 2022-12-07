#ifndef REGISTER_H
#define REGISTER_H

class Register {
public:
	Register();
	~Register();
	unsigned short fetchPC();
	void incrementPC();
	void setPC(unsigned short counter);
	void setRegister(unsigned short opcode);
	void addRegister(unsigned short opcode);
	void setIndex(unsigned short opcode);
	void setI(unsigned short value);
	unsigned short getI();
	void setV(unsigned char index, unsigned char value);
	unsigned char getV(unsigned char index);
	void setSoundTimer(unsigned char value);
	unsigned char getSoundTimer();
	void setDelayTimer(unsigned char value);
	unsigned char getDelayTimer();
private:
	unsigned short PC;
	unsigned short I;
	unsigned char soundTimer;
	unsigned char delayTimer;
	unsigned char* V;
};

#endif