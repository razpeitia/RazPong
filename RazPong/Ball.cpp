#include "Ball.h"

Ball::Ball()
{
	rect = SDL_Rect();
	rect.h = width;
	rect.w = height;
}

void Ball::setup() {
	speedX = std::max(5, rand() % 10);
	speedY = std::max(5, rand() % 10);
	if (rand() % 2 == 0) speedX *= -1;
	if (rand() % 2 == 0) speedY *= -1;
	
	rect.x = Screen::Width / 2;
	rect.y = Screen::Height / 2;
}

int Ball::increaseSpeed(int speed) {
	if (speed < 0) return speed - 1;
	if (speed > 0) return speed + 1;
	return speed;
}

bool Ball::update(std::vector<Player> &players) {
	rect.x += speedX;
	rect.y += speedY;

	if (rect.y < 0) {
		rect.y = 0;
		speedY *= -1;
	}

	if (rect.y > (Screen::Height - rect.h)) {
		rect.y = Screen::Height - rect.h;
		speedY = -1 * speedY;
	}

	for (std::vector<Player>::iterator player = players.begin(); player != players.end(); ++player) {
		// FIXME; If the speed is too high, we will not have a collision
		if (player->collide(&rect)) {
			speedX = increaseSpeed(speedX);
			speedX *= -1;
			speedY = increaseSpeed(speedY);

			// FIXME; Implement stickiness
			if (player->isRigthSide()) {
				rect.x = player->left() - rect.w;
			}
			else {
				rect.x = player->right();
			}
		}

		if (player->isRigthSide()) {
			if (rect.x > Screen::Width) {
				player->score();
				return true;
			}
		}
		else {
			if (rect.x < 0) {
				player->score();
				return true;
			}
		}
	}

	return false;
}

void Ball::draw(Screen *screen) {
	SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(screen->renderer, &rect);
}