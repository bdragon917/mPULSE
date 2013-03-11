#include <SoundEngine/SoundEngine.h>

SoundEngine::SoundEngine(void)
{
	initializeSound();
    printf("Sound Initialized\n");
}

SoundEngine* SoundEngine::getInstance()
{
	static SoundEngine soundEngine;
	return &soundEngine;
}

void SoundEngine::playFinalCountDown()
{
    song->startMusic0();
}

void SoundEngine::toggleMusic()
{
	song->playPause();
}

void SoundEngine::stopMusic()
{
	song->stopMusic();
}

void SoundEngine::engineNoise()
{
	song->playEngine(0);
}

void SoundEngine::engineVol(int engine, int newV)//newV = between 0 - 128
{
	if (engine == 1)
	{
		song->engine1Volume(newV);
	}
	else
		song->engine2Volume(newV);
}


void SoundEngine::crashed(int index)
{
	song->playCrash(index);
}

void SoundEngine::initializeSound()
{
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )  
	{ 
		 printf("Error: No sound\n");
	}

    song = new Sound();
}
