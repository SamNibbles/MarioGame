#include "stdafx.h"
#include "SDL_Setup.h"


CSDL_Setup::CSDL_Setup(bool* quit)
{
	window = NULL;
	window = SDL_CreateWindow("Platformer", 100, 100, 1000, 550, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window could not be created!";
		*quit = true;
	}

	//screenSurface = SDL_GetWindowSurface(window);

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	mainEvent = new SDL_Event();
}


CSDL_Setup::~CSDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

SDL_Renderer* CSDL_Setup::GetRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::GetMainEvent()
{
	return mainEvent;
}

SDL_Surface* CSDL_Setup::GetSurface()
{
	return screenSurface;
}

void CSDL_Setup::Begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::End()
{
	SDL_RenderPresent(renderer);
}
