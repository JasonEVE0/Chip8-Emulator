#ifndef REGISTER_H
#define REGISTER_H

class Register {
public:
	Register();
	~Register();
	unsigned short fetchPC();
	void incrementPC();
private:
	unsigned short PC;
	unsigned short I;
	unsigned char soundTimer;
	unsigned char delayTimer;
	unsigned char* V;
};

#endif