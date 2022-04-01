#pragma once
class CSDL_Setup
{
public:
	CSDL_Setup(bool* quit);
	~CSDL_Setup();

	SDL_Renderer* GetRenderer();
	SDL_Event* GetMainEvent();
	SDL_Surface* GetSurface();

	void Begin();
	void End();

private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;
};

