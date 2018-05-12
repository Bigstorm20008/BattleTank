#pragma once

#include <iostream>
#include <fstream>

#include "SoundEngine.h"

class Sound;
#include "Sound.h"

class SoundFactory
{
public:
	SoundFactory(SoundEngine& soundEngine);
	~SoundFactory();

	Sound* createSoundFromFile(char* filePath);
private:
	SoundEngine* m_pSoundEngine;


};

