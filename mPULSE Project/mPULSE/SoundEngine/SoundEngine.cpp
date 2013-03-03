#include <SoundEngine/SoundEngine.h>

SoundEngine::SoundEngine(void)
{
	initializeSound();
}

SoundEngine* SoundEngine::getInstance()
{
	static SoundEngine soundEngine;
	return &soundEngine;
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

void SoundEngine::initializeSound()
{
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 )  
	{ 
		 printf("Error: No sound\n");
	}

    song = new Sound();
}
