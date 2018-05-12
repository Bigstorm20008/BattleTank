#include "SoundEngine.h"


SoundEngine::SoundEngine()
{
	m_pXAudio2 = nullptr;
	m_pMasterVoice = nullptr;
}


SoundEngine::~SoundEngine()
{
	if (m_pMasterVoice)
	{
		m_pMasterVoice->DestroyVoice();
	}

	//if (m_pXAudio2)
	//{
		//m_pXAudio2->Release();
	//}

	//CoUninitialize();
}

bool SoundEngine::initialize()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CoInitializeEx(0, COINIT_MULTITHREADED)))
	{
		return false;
	}
	

	if (FAILED(hr = XAudio2Create(&m_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		return false;
	}

	if (FAILED(hr = m_pXAudio2->CreateMasteringVoice(&m_pMasterVoice)))
	{
		return false;
	}

	return true;
}

bool SoundEngine::createSourceVoice(IXAudio2SourceVoice* &sourceVoice, WAVEFORMATEX& wfx)
{
	HRESULT hr = S_OK;
	if (FAILED(hr = m_pXAudio2->CreateSourceVoice(&sourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		return false;
	}
	return true;
}
