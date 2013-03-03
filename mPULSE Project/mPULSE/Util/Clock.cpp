#include <Util/Clock.h>
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

unsigned Clock::getCurrentTime()
{
    return SDL_GetTicks();
}

unsigned Clock::getDeltaTime()
{
    unsigned dt = (SDL_GetTicks()-time);
    if(1000.0/maxFrameRate > dt)
    {
        SDL_Delay((1000/60)-(SDL_GetTicks()-time));
        dt = SDL_GetTicks()-time;
    }    
    time = SDL_GetTicks();

return dt;

}

int Clock::getDeltaTime(unsigned prevTime)
{
    return SDL_GetTicks()-prevTime;
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
