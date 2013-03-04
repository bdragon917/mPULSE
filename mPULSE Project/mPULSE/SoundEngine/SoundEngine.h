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
	void engineVol(int engine, int newV);

	void crashed(int index);
	void crashV(int newV);

private:
	SoundEngine();

	Sound* song;

};