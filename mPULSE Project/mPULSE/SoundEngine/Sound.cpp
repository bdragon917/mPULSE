#include <stdio.h>
#include "Sound.h"


Sound::Sound(void)
{
	music = Mix_LoadMUS( "SoundEngine\\Sounds\\10YearsAgoAuda.mp3" );
    if(!music) {
    printf("Mix_LoadMUS: %s\n", Mix_GetError());
    }
}


Sound::~Sound(void)
{
}

bool Sound::check()
{
	if (music == NULL)
	{
		return false;
	}
	else
		return true;
}

void Sound::playPause()
{


	if( check() )
    {
		printf("music ON\n");
	   //if (Mix_PlayMusic(music, -1) ==-1)
       if (Mix_FadeInMusic(music, -1, 10000) ==-1)
	   {
		   printf("problem.\n");
	   }
	  else 
	  { //If the music is paused 
		  if( Mix_PausedMusic() == 1 ) 
		  { //Resume the music 
			  Mix_ResumeMusic(); 
		  } //If the music is playing
		  else 
		  { //Pause the music 
			  //Mix_PauseMusic(); 
		  }
	   }
    }
	else
	{
		printf("music OFF\n");
	}

}

void Sound::stopSound()
{
    Mix_HaltMusic();
	printf("stop\n");
}