#pragma once

#include <iostream>
#include <SDL.h>

class Screen
{
private:
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;
public:
	SDL_Renderer * renderer = NULL;
	static const int Width = 800;
	static const int Height = 600;

	int setup();
	Screen();
	void clear();
	void present();
	void free();
};

