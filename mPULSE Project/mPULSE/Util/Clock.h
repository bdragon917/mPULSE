#pragma once

class Clock
{
public:
    Clock();
    Clock(float frameRateLimit);
    unsigned getCurrentTime();
    float getDeltaTime();
    int getDeltaTime(unsigned prevTime);
    void reset();
    void stop();
    void start();

private:
    unsigned int time;
    float maxFrameRate;
    float milliSecPerFrame;
};