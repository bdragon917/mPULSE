#pragma once

class Clock
{
public:
    Clock();
    Clock(float frameRateLimit);
    unsigned getCurrentTime();
    unsigned getDeltaTime();
    int getDeltaTime(unsigned prevTime);
    void reset();
    void stop();
    void start();

private:
    unsigned int time;
    float maxFrameRate;
    float milliSecPerFrame;
};