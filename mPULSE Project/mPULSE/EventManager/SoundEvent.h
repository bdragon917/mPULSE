#pragma once
class SoundEvent
{
public:
    SoundEvent(int channel,int soundIndex);
    ~SoundEvent(void);
    int ch;
    int sIndex;
};

