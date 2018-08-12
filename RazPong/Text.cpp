#include "Text.h"

TTF_Font* Text::font = NULL;

Text::Text(Screen *screen, int x, int y, const char *text)
{
	rect.x = x;
	rect.y = y;
	this->text = text;

	SDL_Surface *surface = TTF_RenderText_Blended(Text::font, text, textColor);
	texture = SDL_CreateTextureFromSurface(screen->renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}

void Text::updateText(Screen *screen, const char* text) {
	if (strcmp(text, this->text) == 0) return;
	this->text = text;
	SDL_Surface *surface = TTF_RenderText_Blended(Text::font, text, textColor);
	texture = SDL_CreateTextureFromSurface(screen->renderer, surface);
	rect.w = surface->w;
	rect.h = surface->h;
	SDL_FreeSurface(surface);
}

void Text::draw(Screen *screen) {
	SDL_RenderCopy(screen->renderer, texture, NULL, &rect);
}

int Text::init() {
	TTF_Init();
	Text::font = TTF_OpenFont("Inconsolata.ttf", 40);
	if (Text::font == NULL) {
		std::cerr << "error: font not found\n";
		return 4;
	}
	return 0;
}

void Text::free() {
	// SDL_DestroyTexture(texture);
	TTF_Quit();
}
