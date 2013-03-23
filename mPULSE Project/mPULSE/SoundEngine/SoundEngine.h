#include <stdio.h>
#include "Sound.h"

#pragma once
class SoundEngine
{
public:
	static SoundEngine* getInstance();

	void initializeSound();

	//void loadMusic();

	void toggleMusic();
	void stopMusic();
    void FadeOutMusic(int ms);

    void SoundEngine::playFinalCountDown();
	void engineNoise();
	void engineVol(int engine, int newV);

    void playSound(int channel, int index);

	void crashed(int index);
	void crashV(int newV);

private:
	SoundEngine();

	Sound* song;

};