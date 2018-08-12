#include "Screen.h"

Screen::Screen()
{
	
}

void Screen::clear() {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}

int Screen::setup() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL initialization failed. SDL Error: " << SDL_GetError();
		return 1;
	}

	window = SDL_CreateWindow("RazPong v0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		std::cerr << "Could not create window. SDL Error: " << SDL_GetError();
		return 2;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		std::cerr << "Could not create renderer. SDL Error: " << SDL_GetError();
		return 3;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	screenSurface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);
}

void Screen::present() {
	SDL_RenderPresent(renderer);
}


void Screen::free()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
