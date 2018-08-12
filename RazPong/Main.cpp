#include <iostream>
#include <algorithm>
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include "Player.h"
#include "Screen.h"
#include "Ball.h"
#include "Separator.h"
#include "Text.h"

using namespace std;

const int FRAMES_PER_SECOND = 30;

int main(int argc, char * argv[])
{
	
	SDL_Event event;
	bool done = false;
	Uint32 lastTick, elapsedMs;
	
	bool reset = false;
	bool hardReset = false;

	Screen screen;
	int result = screen.setup();
	if (result != 0) {
		return result;
	}

	result = Text::init();
	if (result != 0) {
		return result;
	}

	vector<Player> players;
	Text text1 = Text(&screen, 3 * (Screen::Width / 4), 0, "0");
	Text text2 = Text(&screen, Screen::Width / 4, 0, "0");
	players.push_back(Player(&text1, true, 300, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN));
	players.push_back(Player(&text2, false, -300, SDL_SCANCODE_W, SDL_SCANCODE_S));
	
	Ball ball;
	ball.setup();

	Separator separator;

	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

	while (!done) {
		lastTick = SDL_GetTicks();

		if (reset) {
			reset = false;
			ball.setup();
			for (vector<Player>::iterator player = players.begin(); player != players.end(); ++player) {
				player->resetPos();
				if (hardReset) {
					player->score_ = 0;
				}
			}
			if (hardReset) hardReset = false;
		}

		// Event handling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;

			default:
				break;
			}
		}

		if (keyboardState[SDL_SCANCODE_Q]) {
			done = true;
		}

		for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			it->update(keyboardState);
		}
		reset = ball.update(players);
		
		for (vector<Player>::iterator it = players.begin(); it != players.end(); ++it) {
			// FIXME; Make this variable
			// This include not hardcoding Player.arr
			if (it->score_ >= 10) {
				hardReset = true;
				break;
			}
		}
		if (hardReset) continue;

		// Render update
		screen.clear();
		for (vector<Player>::iterator player = players.begin(); player != players.end(); ++player) {
			player->draw(&screen);
		}
		ball.draw(&screen);
		separator.draw(&screen);
		screen.present();

		// Throttling
		elapsedMs = (SDL_GetTicks() - lastTick);
		if (elapsedMs < (1000 / FRAMES_PER_SECOND))
		{
			SDL_Delay((1000 / FRAMES_PER_SECOND) - elapsedMs);
		}
	}

	text1.free();
	text2.free();
	Text::free();
	screen.free();
	
	return 0;
}
