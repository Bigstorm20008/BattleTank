#pragma once

#include <xaudio2.h>



class SoundEngine
{
public:
	SoundEngine();
	~SoundEngine();

	bool initialize();
	bool createSourceVoice(IXAudio2SourceVoice* &sourceVoice, WAVEFORMATEX &wfx);
private:
	IXAudio2* m_pXAudio2;
	IXAudio2MasteringVoice* m_pMasterVoice;
};

