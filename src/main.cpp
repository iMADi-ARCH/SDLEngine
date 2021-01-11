#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

void init ()
{
	// INITIALIZIING 
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL_INIT FAILED! \n" << SDL_GetError() << std::endl;
	}

	if ( !(IMG_Init(IMG_INIT_PNG)) )
	{
		std::cout << "IMG_Init FAILED! \n" << SDL_GetError() << std::endl;
	}

}

int main (int argc, char* args[])
{
	// VARS
	RenderWindow window("Game v1.0", 600, 600);

	SDL_Texture* tile0 = window.loadTexture("res/gfx/Tile001.png");

	// Entities list
	std::vector<Entity> entities;

	for (int i=0; i <= 5; i ++)
	{
		Entity temp_e(Vector2f(i*32, 0), tile0);
		entities.push_back(temp_e);
	}


	bool gameRunning = true;

	SDL_Event event;

	while (gameRunning)
	{
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
		}

		window.clear();
		

		for (Entity& e : entities)
		{ 
			window.render(e);
		}


		window.display();

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}