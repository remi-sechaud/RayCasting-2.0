#pragma once
#include <SDL.h>


class Timer
{
    private:
        int startTicks;
        int pausedTicks;
        bool paused;
        bool started;
 
    public:
        Timer();
        void start();
        void stop();
        void pause();
        void unpause();
        int getTicks();
};