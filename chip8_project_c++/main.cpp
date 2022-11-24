#include <iostream>
#include <SDL.h>
#include <stdlib.h>
#include <fstream>
#include "Emulator.h"

int main(int argc, char* argv[]) {
	Emulator* emulator = new Emulator();

	// declare buffer and open file
	unsigned char* memoryBlock;
	std::ifstream stream(argv[1], std::ios::in | std::ios::binary | std::ios::ate);

	// get size and set pointer back to zero, instantiate buffer
	int size = stream.tellg();
	stream.seekg(0, std::ios::beg);
	memoryBlock = new unsigned char[size];

	// read the file into the buffer
	if (stream.is_open()) {
		stream.read((char*)memoryBlock, size);
		stream.close();
	}

	// load buffer into memory

	// print the contents of the buffer
	//for (int i = 0; i < size; i++) {
	//	printf("%x\n", memoryBlock[i]);
	//}

	unsigned short ti = emulator->fetch();
	printf("%x\n", ti);

	// Init SDL and create SDL window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("CHIP8 EMULATOR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);

	bool running = true;
	SDL_Event* event = new SDL_Event();
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	while (running) {
		SDL_PollEvent(event);

		if (event->type == SDL_QUIT) {
			running = false;
			break;
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 1);
		SDL_Rect* rect = new SDL_Rect();
		rect->x = 50;
		rect->y = 50;
		rect->w = 10;
		rect->h = 10;

		SDL_RenderFillRect(renderer, rect);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}