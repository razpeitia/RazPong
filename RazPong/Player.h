#pragma once
#include<string>
#include<sstream>

#include<SDL.h>

#include "Screen.h"
#include "Text.h"

class Player {
private:
	SDL_Rect rect;
	int width = 10;
	int height = 60;
	int speed = 20;
	int offset;
	SDL_Scancode up;
	SDL_Scancode down;
	bool rightSide;
	Text *scoreText;
	const char *arr[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };

public:
	Player(Text *scoreText, bool rightSide_, int offset_, SDL_Scancode up_, SDL_Scancode down_);
	void resetPos();
	void draw(Screen *screen);
	void update(const Uint8 *keyboardState);
	int left();
	int right();
	bool collide(SDL_Rect *rect_);
	void score();
	bool isRigthSide();
	int score_ = 0;
};

