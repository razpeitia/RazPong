#include "Separator.h"

Separator::Separator()
{
	rect.h = height;
	rect.w = width;
	rect.x = (Screen::Width / 2) - (width / 2);
}

void Separator::draw(Screen *screen) 
{
	SDL_SetRenderDrawColor(screen->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	for (rect.y = 0; rect.y < Screen::Height; rect.y += (height + offset))
	{
		SDL_RenderFillRect(screen->renderer, &rect);
	}
}
