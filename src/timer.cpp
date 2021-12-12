#include "timer.hpp"


Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
	if(!started)
	{
    	started = true;
   		paused = false;
   		startTicks = SDL_GetTicks();
   	}
 
    
}

void Timer::stop()
{
    started = false;
 
    paused = false;
}

int Timer::getTicks()
{
    if(started == true)
    {
        if(paused == true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
 
    return 0;
}

void Timer::pause()
{
    if((started == true) && (paused == false))
    {
        paused = true;
 
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    if(paused == true)
    {
        paused = false;
 
        startTicks = SDL_GetTicks() - pausedTicks;
 
        pausedTicks = 0;
    }
}