#include <SoundEngine/Sound.h>
#include <iostream>

Sound::Sound(void)
{
	music = Mix_LoadMUS( "SoundEngine\\Sounds\\10YearsAgoAuda.mp3" );
    if(!music) {
        std::cout << "Mix_LoadMUS: " << Mix_GetError() << std::endl;
    }
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
       std::cout << "music ON" << std::endl;
	   //if (Mix_PlayMusic(music, -1) ==-1)
       if (Mix_FadeInMusic(music, -1, 10000) ==-1)
	   {
		   std::cout << "problem." << std::endl;
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
		std::cout << "music OFF" << std::endl;
	}

}

void Sound::stopSound()
{
    Mix_HaltMusic();
	std::cout << "stop" << std::endl;
}
