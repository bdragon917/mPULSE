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
	void engineNoise();

private:
	SoundEngine();

	Sound* song;

};