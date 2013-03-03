#include <SoundEngine/Sound.h>

#pragma once
class SoundEngine
{
public:
	static SoundEngine* getInstance();

	void initializeSound();

	//void loadMusic();

	void toggleMusic();
	void stopMusic();
private:
	SoundEngine();

	Sound* song;
};
