#include "Sound.h"


Sound::Sound(void)
{
	SOUND_LIST = "sounds.txt";

	musicTrack = 0;
	
	char charArray[1024];
	std::ifstream file;
    std::vector<std::string> soundFileNames;
    std::string tmpName;

	file.open(SOUND_LIST);	

    if(file.is_open())
    {
	    while(!file.eof())
	    {
            file.getline(charArray,1024);
			chunks.push_back(Mix_LoadWAV(charArray));
	    }
	    file.close();

		music1 = Mix_LoadMUS( "SoundEngine\\Sounds\\OuterSpace.mp3" );
		music2 = Mix_LoadMUS( "SoundEngine\\Sounds\\10YearsAgoAuda.mp3" );
	}

	if(!music1) 
	{
		printf("Mix_LoadMUS: %s\n", Mix_GetError());
	}
}


Sound::~Sound(void)
{
}

bool Sound::check()
{
	if (music1 == NULL)
	{
		printf("music1 missing");
		return false;
	}
	if (music2 == NULL)
	{
		printf("music2 missing");
		return false;
	}
	
	return true;
}

void Sound::playPause()
{
	if( check() )
    {
		if (Mix_PlayingMusic() == 0)
		{
			if (musicTrack == 0)
				startMusic1();
			else if (musicTrack == 1)
				startMusic2();
		}
		else 
		{
			 //If the music is paused 
			  if( Mix_PausedMusic() == 1 ) 
			  { //Resume the music 
				  Mix_ResumeMusic(); 
			  } //If the music is playing
			  else 
			  { //Pause the music 
				  Mix_PauseMusic(); 
			  }
		}
    }
	else
	{
		printf("music OFF\n");
	}

}

void Sound::startMusic1()
{
	Mix_FadeInMusic(music1, 1, 10000);
}

void Sound::startMusic2()
{
	Mix_FadeInMusic(music2, 1, 10000);
}

void Sound::stopMusic()
{
    Mix_HaltMusic();
	printf("stop\n");
}

void Sound::playEngine(int index)
{
	engine1Channel = Mix_PlayChannel( 0, chunks.at(index), -1 );
	engine2Channel = Mix_PlayChannel( 1, chunks.at(index), -1 );
}

void Sound::engine1Volume(int newV)
{
	Mix_Volume(engine1Channel, newV);
}

void Sound::engine2Volume(int newV)
{
	Mix_Volume(engine2Channel, newV);
}

void Sound::playCrash(int index)
{
	crashChannel = Mix_PlayChannel( 2, chunks.at(5 + index), 0);
}

void Sound::crashVolume(int newV)
{
	Mix_Volume(crashChannel, newV);
}
