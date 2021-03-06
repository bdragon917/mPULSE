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
    lastUsedFPS = 0;
    lastUsedFPSAtTime = 0;
    FPSTimeSwitchLimit = 5000;
}

unsigned Clock::getCurrentTime()
{
    return SDL_GetTicks();
}

float Clock::getDeltaTime()
{	
    float dt = (float)(SDL_GetTicks()-time);

	if(2.0f*milliSecPerFrame > dt)
	{
		SDL_Delay((unsigned)((2.0f*milliSecPerFrame)-dt)); //Wait for the difference
        dt = 2.0f*milliSecPerFrame;   //Calculate new dt
	}
	else if(3.0f*milliSecPerFrame > dt)
	{
		SDL_Delay((unsigned)((3.0f*milliSecPerFrame)-dt)); //Wait for the difference
        dt = 3.0f*milliSecPerFrame;   //Calculate new dt        
	}
    time = SDL_GetTicks(); //update previous time

	return dt;


//Attempt at capping the frequency of FPS switching.

 //   float dt = (float)(SDL_GetTicks()-time);
 //   if(milliSecPerFrame > dt && getDeltaTime(lastUsedFPSAtTime) > FPSTimeSwitchLimit)
 //   {        
 //       SDL_Delay((unsigned)(milliSecPerFrame-dt)); //Wait for the difference
 //       dt = milliSecPerFrame;   //Calculate new dt

 //       lastUsedFPSAtTime = milliSecPerFrame;
 //   }
	//else if(((2.0f*milliSecPerFrame) > dt) && ((getDeltaTime(lastUsedFPSAtTime) > FPSTimeSwitchLimit) || (lastUsedFPS >= (2.0f*milliSecPerFrame))))
	//{
	//	SDL_Delay((unsigned)((2.0f*milliSecPerFrame)-dt)); //Wait for the difference
 //       dt = 2.0f*milliSecPerFrame;   //Calculate new dt

 //       if(lastUsedFPS != 2.0f*milliSecPerFrame)
 //           lastUsedFPSAtTime = getCurrentTime();

 //       lastUsedFPS = 2.0f*milliSecPerFrame;
	//}
	//else if(((3.0f*milliSecPerFrame) > dt) && ((getDeltaTime(lastUsedFPSAtTime) > FPSTimeSwitchLimit) || (lastUsedFPS >= (3.0f*milliSecPerFrame))))
	//{
	//	SDL_Delay((unsigned)((3.0f*milliSecPerFrame)-dt)); //Wait for the difference
 //       dt = 3.0f*milliSecPerFrame;   //Calculate new dt        

 //       if(lastUsedFPS != 3.0f*milliSecPerFrame)
 //           lastUsedFPSAtTime = getCurrentTime(); 

 //       lastUsedFPS = 3.0f*milliSecPerFrame;
	//}
 //   time = SDL_GetTicks(); //update previous time

	//return dt;

}

int Clock::getDeltaTime(unsigned prevTime)
{
    return SDL_GetTicks()-prevTime;
}

void Clock::reset()
{
    time = 0;
}

void Clock::stop()
{

}

void Clock::start()
{


}
