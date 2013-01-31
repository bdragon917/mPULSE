#pragma once

class Clock
{
public:
    Clock();
    Clock(int frameRateLimit);
    unsigned int getCurrentTime();
    unsigned int getDeltaTime();
    void reset();
    void stop();
    void start();

private:
    unsigned int time;
    int maxFrameRate;
};