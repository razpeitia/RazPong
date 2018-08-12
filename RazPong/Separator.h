#pragma once

#include <SDL.h>
#include "Screen.h"

class Separator
{
private:
	int width = 5, height = 20, offset = 14;
	SDL_Rect rect;

public:
	Separator();
	void draw(Screen *screen);
};

