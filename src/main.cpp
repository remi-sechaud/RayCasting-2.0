#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <iostream>
#include "game.hpp"
#include "timer.hpp"


int main(int argc , char *args[])
{
	SDL_Init(SDL_INIT_VIDEO);

	Game game;

	SDL_ShowCursor(SDL_DISABLE);

	Timer timer;

	SDL_Event event;

	bool running = true;

	while(running)
	{
		SDL_PollEvent(&event);

		SDL_GetMouseState(&game.mouse_pos[0],&game.mouse_pos[1]);

		timer.start();

		switch(event.type)
		{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						game.turning_left = true;
						break;
					case SDLK_RIGHT:
						game.turning_right = true;
						break;
					case SDLK_z:
						game.input[0] = true;
						break;
					case SDLK_q:
						game.input[1] = true;
						break;
					case SDLK_s:
						game.input[2] = true;
						break;
					case SDLK_d:
						game.input[3] = true;
						break;
					case SDLK_ESCAPE:
						running = false;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_LEFT:
						game.turning_left = false;
						break;
					case SDLK_RIGHT:
						game.turning_right = false;
						break;
					case SDLK_z:
						game.input[0] = false;
						break;
					case SDLK_q:
						game.input[1] = false;
						break;
					case SDLK_s:
						game.input[2] = false;
						break;
					case SDLK_d:
						game.input[3] = false;
						break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
                /*if(event.button == SDL_BUTTON_LEFT)
                {
                	*/game.shoot();/*
                }*/
                break;
		
		}
		game.nextFrame();
		timer.stop();
		

	}

	game.cleanUp();
	SDL_Quit();


	return 0;
}
