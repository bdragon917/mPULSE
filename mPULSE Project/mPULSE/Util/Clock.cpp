#include <Util/Clock.h>
#include <SDL.h>

Clock::Clock()
{
    time = 0;
}

Clock::Clock(float frameRateLimit)
{
    time = 0;
    maxFrameRate = frameRateLimit;
    milliSecPerFrame = 1000.0f/frameRateLimit;
}

unsigned Clock::getCurrentTime()
{
    return SDL_GetTicks();
}

unsigned Clock::getDeltaTime()
{
    unsigned dt = SDL_GetTicks()-time;
    if(milliSecPerFrame > dt)//Cap the clock at 60FPS
    {
        SDL_Delay((unsigned)milliSecPerFrame-dt); //Wait for the difference
        dt = SDL_GetTicks()-time;   //Calculate new dt
    }        
    time = SDL_GetTicks(); //update previous time

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
