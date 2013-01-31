#include "Clock.h"
#include <SDL.h>

Clock::Clock()
{
    time = 0;
}

Clock::Clock(int frameRateLimit)
{
    time = 0;
    maxFrameRate = frameRateLimit;
}

unsigned int Clock::getCurrentTime()
{
    return SDL_GetTicks();
}

unsigned int Clock::getDeltaTime()
{
    unsigned int dt = (SDL_GetTicks()-time);
    if(1000.0/maxFrameRate > dt)
    {
        SDL_Delay((1000/60)-(SDL_GetTicks()-time));
        dt = SDL_GetTicks()-time;
    }    
    time = SDL_GetTicks();

return dt;

}

void Clock::reset()
{

}

void Clock::stop()
{

}

void Clock::start()
{


}