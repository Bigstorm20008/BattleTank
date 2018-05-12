#include "SoundFactory.h"


SoundFactory::SoundFactory(SoundEngine& soundEngine)
{
	m_pSoundEngine = &soundEngine;
}


SoundFactory::~SoundFactory()
{
}

Sound* SoundFactory::createSoundFromFile(char* filePath)
{
	std::ifstream fin(filePath, std::ifstream::in | std::ifstream::binary);

	if (!fin.is_open())
	{
		return nullptr;
	}


	Sound* sound = new Sound;

	WAVEFORMATEX* wfx = &(sound->m_wfx);
	wfx->wFormatTag = WAVE_FORMAT_PCM;
	wfx->cbSize = 0;


	char chunkId[5];
	memset(chunkId, 0, sizeof(chunkId));
	fin.read(chunkId, 4);
	if (strcmp(chunkId, "RIFF") != 0)
	{
		delete sound;
		sound = nullptr;
		fin.close();
		return nullptr;	
	}

	unsigned long chunkSize = 0;
	fin.read((char*)&chunkSize, sizeof(chunkSize));

	char format[6];
	memset(format, 0, sizeof(format));
	fin.read((char*)&format, 4);
	if (strcmp(format, "WAVE") != 0)
	{
		delete sound;
		sound = nullptr;
		fin.close();
		return nullptr;
	}
	
	char subChunk1Id[6];
	memset(subChunk1Id, 0, sizeof(subChunk1Id));
	fin.read((char*)&subChunk1Id, 4);
	if (strcmp(subChunk1Id, "fmt ") != 0)
	{
		delete sound;
		sound = nullptr;
		fin.close();
		return nullptr;
	}

	unsigned long subChunk1Size;
	fin.read((char*)&subChunk1Size, sizeof(subChunk1Size));

	unsigned short int audioFormat;
	fin.read((char*)&audioFormat, sizeof(audioFormat));
	if (audioFormat != 1)
	{
		delete sound;
		sound = nullptr;
		fin.close();
		return nullptr;
	}
	
	fin.read((char*)&wfx->nChannels, sizeof(wfx->nChannels));
	fin.read((char*)&wfx->nSamplesPerSec, sizeof(wfx->nSamplesPerSec));
	fin.read((char*)&wfx->nAvgBytesPerSec, sizeof(wfx->nAvgBytesPerSec));
	fin.read((char*)&wfx->nBlockAlign, sizeof(wfx->nBlockAlign));
	fin.read((char*)&wfx->wBitsPerSample, sizeof(wfx->wBitsPerSample));


	char subChunk2Id[5];
	memset(subChunk2Id, 0, sizeof(subChunk2Id));
	fin.read((char*)&subChunk2Id, 4);
	if (strcmp(subChunk2Id, "data") != 0)
	{
		delete sound;
		sound = nullptr;
		fin.close();
		return nullptr;
	}
	unsigned long subChunk2Size;
	fin.read((char*)&subChunk2Size, sizeof(subChunk2Size));

	char* data = new char[subChunk2Size];
	fin.read(data, subChunk2Size);
	fin.close();

	memset(&sound->m_buffer, 0, sizeof(sound->m_buffer));
	sound->m_buffer.AudioBytes = subChunk2Size;
	sound->m_buffer.pAudioData = (BYTE*)data;
	sound->m_buffer.Flags = XAUDIO2_END_OF_STREAM;

	m_pSoundEngine->createSourceVoice(sound->m_pSourceVoice, sound->m_wfx);

	sound->m_pSourceVoice->SubmitSourceBuffer(&sound->m_buffer);


	return sound;
}
