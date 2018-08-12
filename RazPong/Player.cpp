#include "Player.h"

Player::Player(Text *scoreText, bool rightSide_, int offset_, SDL_Scancode up_, SDL_Scancode down_) {
	rightSide = rightSide_;
	up = up_;
	down = down_;
	offset = offset_;
	rect.h = height;
	rect.w = width;
	resetPos();
	this->scoreText = scoreText;
}

void Player::resetPos() {
	rect.x = (Screen::Width / 2) + offset;
	rect.y = Screen::Height / 2;
}

void Player::draw(Screen *screen) {
	scoreText->updateText(screen, arr[this->score_]);
	scoreText->draw(screen);
	SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(screen->renderer, &rect);
}

void Player::update(const Uint8 *keyboardState) {
	if (keyboardState[up]) {
		rect.y -= speed;
	}
	else if (keyboardState[down]) {
		rect.y += speed;
	}

	if (rect.y < 0) {
		rect.y = 0;
	}
	if (rect.y > (Screen::Height - rect.h)) {
		rect.y = Screen::Height - rect.h;
	}
}

int Player::left() {
	return rect.x;
}

int Player::right() {
	return rect.x + rect.w;
}

bool Player::collide(SDL_Rect *rect_) {
	return SDL_HasIntersection(&rect, rect_) == SDL_TRUE;
}

void Player::score() {
	this->score_ += 1;
}

bool Player::isRigthSide() {
	return rightSide;
}