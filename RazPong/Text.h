#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include"Screen.h"

class Text
{
private:
	static TTF_Font *font;
	const char *text;
	SDL_Rect rect;
	SDL_Color textColor = { 255, 255, 255, 0 };
	SDL_Texture *texture;
public:
	Text(Screen *screen, int x, int y, const char *text);
	void updateText(Screen *screen, const char * text);
	void draw(Screen *screen);
	static int init();
	static void free();
};