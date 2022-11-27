#ifndef MEMORY_H
#define MEMORY_H

#include <stack>

class Memory
{
public:
	Memory();
	~Memory();
	void storeMemory(unsigned char* programMemory, int index, int size);
	unsigned char getMemoryCell(int index);
	void push(unsigned short value);
	void pop();
	unsigned short peek();
private:
	unsigned char* memory;
	unsigned char* font;
	std::stack<unsigned short> stack;
};

#endif