#include "SoundEngine.h"


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
	song->stopSound();
}

void SoundEngine::initializeSound()
{
    /*
    int flags = MIX_INIT_MP3;                   //I think this code will flag an error if mp3 decoding is not possible???
    int retVal = Mix_Init(flags);
    //printf("Sound Initialization: %i\n", retVal);
    if((retVal&flags) != flags) {
        printf("Mix_Init: Failed to init required ogg and mod support!\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        // handle error

    }*/
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1 ) 
    //if( Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) == -1 ) 
	{ 
		 printf("Error: No sound\n");
	}

    song = new Sound();
}