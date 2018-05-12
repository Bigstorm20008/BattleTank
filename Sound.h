#pragma once

#include <xaudio2.h>


class SoundFactory;
//#include "SoundFactory.h"


class Sound
{

friend SoundFactory;

public:
	Sound();
	~Sound();
	void play();
	void stop();
	void restart();
	void setVolume(float volume);

	bool isPlaying();
private:
	WAVEFORMATEX m_wfx;
	XAUDIO2_BUFFER m_buffer;

	IXAudio2SourceVoice* m_pSourceVoice;
};

