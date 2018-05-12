#include "Sound.h"


Sound::Sound()
{
}


Sound::~Sound()
{
	if (m_buffer.pAudioData)
	{
		delete m_buffer.pAudioData;
		m_buffer.pAudioData = nullptr;
	}
}

void Sound::play()
{
	m_pSourceVoice->Start();
}

void Sound::stop()
{
	m_pSourceVoice->Stop();
}

void Sound::restart()
{
	m_pSourceVoice->FlushSourceBuffers();
	m_pSourceVoice->SubmitSourceBuffer(&m_buffer);
}

bool Sound::isPlaying()
{
	XAUDIO2_VOICE_STATE state;
	m_pSourceVoice->GetState(&state);
	if (state.BuffersQueued == 0)
	{
		return false;
	}

	return true;
		
}

void Sound::setVolume(float volume)
{
	m_pSourceVoice->SetVolume(volume);
}