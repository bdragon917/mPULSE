#pragma once

//#include "SDL_audio.h"
#include "SDL_mixer.h"

class Sound
{
	public:
		Sound(void);
		~Sound(void);

		void playPause();
		void stopSound();

		bool Sound::check();
	private:
		Mix_Music *music;
};