#pragma once
#include <vector>
#include <algorithm>

#include <SDL.h>
#include "Player.h"
#include "Screen.h"

class Ball
{
private:
	int screenWidth, screenHeight;
	int width = 10, height = 10;
	int speedX, speedY;

	int increaseSpeed(int speed);

public:
	SDL_Rect rect;
	Ball();

	void setup();
	bool update(std::vector<Player> &players);
	void draw(Screen *screen);
};