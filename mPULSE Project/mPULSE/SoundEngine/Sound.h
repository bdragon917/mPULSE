#pragma once

//#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>

class Sound
{
	public:
		Sound(void);
		~Sound(void);

		void playPause();
		void stopMusic();

		bool Sound::check();

		void playEngine(int index);
		void engine1Volume(int newV);
		void engine2Volume(int newV);

		void playCrash(int index);
        void playSound(int channel, int index);
        void playSound(int index);
        void fadeOutAllSound(int ms);
		void crashVolume(int newV);

        void fadeOutMusic(int ms);

        void startMusic0();
		void startMusic1();
		void startMusic2();

	private:
        Mix_Music *music0;
		Mix_Music *music1;
		Mix_Music *music2;
		std::vector <Mix_Chunk*> chunks;

		std::string SOUND_LIST;

		int musicTrack;

		int engine1Channel;
		int engine2Channel;
		int crashChannel;
};