#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

const int SCALE = 1;

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL), w(p_w), h(p_h)
{
	window = SDL_CreateWindow(
		p_title, 
		SDL_WINDOWPOS_UNDEFINED, 
		SDL_WINDOWPOS_UNDEFINED, 
		p_w, p_h, 
		SDL_WINDOW_SHOWN);

	if (window==NULL)
	{
		std::cout << "WINDOW failed to init! \n" << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "IMG/Texture Failed to Load! \n" << SDL_GetError() << std::endl;

	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);

	SDL_DisplayMode mode;

	SDL_GetDisplayMode(displayIndex, 0, &mode);

	return mode.refresh_rate;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x * SCALE;
	dst.y = p_entity.getPos().y * SCALE;
	dst.w = p_entity.getCurrentFrame().w * SCALE;
	dst.h = p_entity.getCurrentFrame().h * SCALE;

	SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
