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
	emulator->storeMemory(memoryBlock, 512, size);

	// Init SDL and create SDL window
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("CHIP8 EMULATOR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 320, SDL_WINDOW_SHOWN);

	bool running = true;
	SDL_Event* event = new SDL_Event();
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// Event loop
	while (running) {
		SDL_PollEvent(event);

		if (event->type == SDL_QUIT) {
			running = false;
			break;
		}

		// map real key to virtual key
		if (event->type == SDL_KEYDOWN) {
			char rKey = event->key.keysym.sym;
			char vKey = emulator->convertKey(rKey);
		}

		// fetch instruction
		unsigned short instruction = emulator->fetch();

		// execute instruction
		emulator->execute(instruction);

		// draw the screen
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
		int scale = 10;
		for (int x = 0; x < 64; x++) {
			for (int y = 0; y < 32; y++) {
				if (emulator->isPixelOn(x,y)){
					SDL_Rect* pixel = new SDL_Rect();
					pixel->x = x * scale;
					pixel->y = y * scale;
					pixel->w = scale;
					pixel->h = scale;
					SDL_RenderFillRect(renderer, pixel);
				}
			}
		}

		// render the screen
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}