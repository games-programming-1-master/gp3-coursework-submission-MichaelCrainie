#pragma once

#ifndef _SOUND_H
#define _SOUND_H

// OpenGL Headers
#include "pch.h"
#include "Common.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class cSound
{
private:
	Mix_Chunk* SoundFX = NULL;
	Mix_Music* sMusic = NULL;
	soundType theSoundType;

public:
	cSound();
	cSound(soundType sndType);
	~cSound();

	bool load(const string filename);
	void setSoundType(soundType andType);
	soundType getSoundType();
	void play(int loop); // use -1 for indinate loop
	void PlayMusic();
	void StopMusic();
};

#endif

