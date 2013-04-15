#include "Sound.h"


Sound::Sound(void)
{
	SOUND_LIST = "sounds.txt";
	MUSIC_LIST = "music.txt";

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

        //music0 = Mix_LoadMUS( "SoundEngine\\Sounds\\FinalCountdown.mp3");
		//music1 = Mix_LoadMUS( "SoundEngine\\Sounds\\OuterSpace.mp3" );
		//music2 = Mix_LoadMUS( "SoundEngine\\Sounds\\10YearsAgoAuda.mp3" );
	}

	//if(!music1) 
	//{
		//printf("Mix_LoadMUS: %s\n", Mix_GetError());
	//}

	file.open(MUSIC_LIST);
	if (file.is_open())
	{
		while (!file.eof())
		{
			file.getline(charArray,1024);
			Mix_Music* aMusic = Mix_LoadMUS(charArray);


			if (aMusic == NULL)
			{printf("Sound.cpp: "); printf(charArray); printf(" can't be loaded!\n");}

			music.push_back(aMusic);
			music;
		}

		file.close();
	}
}


Sound::~Sound(void)
{
}

bool Sound::check()
{
	/*
	if (music.at(0) == NULL)
	{
		printf("music1 missing");
		return false;
	}
	if (music.at(1) == NULL)
	{
		printf("music2 missing");
		return false;
	}
	*/

	for (unsigned int i = 0; i < music.size(); i++)
	{
		if (music.at(i) == NULL)
		{
			printf("music missing: %u\n", i);
			return false;
		}
	}
	
	return true;
}

//only plays if there is a track running as well.
void Sound::playPause()
{
	if( check() )
    {
		if (Mix_PlayingMusic() == 0)
		{
			//if (musicTrack == 0)
				//startMusic2();
			//else if (musicTrack == 1)
				//startMusic1();
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


void Sound::startMusic0()
{
	Mix_FadeInMusic(music.at(0), 1, 1000);
}
void Sound::startMusic0Infinite()
{
	Mix_FadeInMusic(music.at(0), -1, 1000);
}

void Sound::startMusic1()
{
	Mix_FadeInMusic(music.at(1), 1, 1000);
}
void Sound::startMusic1Infinite()
{
	Mix_FadeInMusic(music.at(1), -1, 1000);
}

void Sound::startMusic2()
{
	Mix_FadeInMusic(music.at(2), 1, 1000);
}
void Sound::startMusic2Infinite()
{
	Mix_FadeInMusic(music.at(2), -1, 1000);
}

void Sound::startMusicInfinite(int i)
{
	int retVal = Mix_FadeInMusic(music.at(i), -1, 1000);

	printf("Sound.cpp: retVal:%i\n", retVal);
}

void Sound::fadeOutMusic(int ms)
{
    Mix_FadeOutMusic(ms);
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

void Sound::playSound(int inChannel, int inIndex)
{
    Mix_PlayChannel(inChannel, chunks.at(inIndex), 0);
}

void Sound::playSound(int inIndex)
{
    Mix_PlayChannel(-1, chunks.at(inIndex), 0);
}

void Sound::fadeOutAllSound(int ms)
{
    Mix_FadeOutChannel(-1, ms);
}

void Sound::crashVolume(int newV)
{
	Mix_Volume(crashChannel, newV);
}
