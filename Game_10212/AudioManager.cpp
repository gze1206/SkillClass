#include "DXUT.h"
#include "AudioManager.h"
#include "GameManager.h"

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
	if (engine)
	{
		engine->ShutDown();
		engine->Release();
	}
	if (soundBankData)
		delete[] soundBankData;
	soundBankData = NULL;
	if (mapWaveBank)
		UnmapViewOfFile(mapWaveBank);
	mapWaveBank = NULL;
	if (initialized)
		CoUninitialize();
}

HRESULT AudioManager::initAudio()
{
	HRESULT hr;
	initialized = CoInitialize(NULL)==S_OK;
	XACT3CreateEngine(0, &engine);
	if (engine == NULL) return E_FAIL;
	XACT_RUNTIME_PARAMETERS Params = { 0 };
	Params.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	hr = engine->Initialize(&Params);
	HANDLE hFile = CreateFile(L"Audio/Wave Bank.xwb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD filesize = GetFileSize(hFile, NULL);
		if (filesize != -1)
		{
			HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, filesize, NULL);
			if (hMapFile)
			{
				LPVOID mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
				if (mapWaveBank)
					hr = engine->CreateInMemoryWaveBank(mapWaveBank, filesize, 0, 0, &wave);
				CloseHandle(hMapFile);
			}
		}
		CloseHandle(hFile);
	}
	if (hr)
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	hr = E_FAIL;
	hFile = CreateFile(L"Audio/Sound Bank.xsb", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD filesize = GetFileSize(hFile, NULL);
		if (filesize != -1)
		{
			soundBankData = new BYTE[filesize];
			if (soundBankData)
			{
				DWORD bytesRead;
				if (0 != ReadFile(hFile, soundBankData, filesize, &bytesRead, NULL))
					hr = engine->CreateSoundBank(soundBankData, filesize, 0, 0, &sound);
			}
		}
		CloseHandle(hFile);
	}
	if (hr)
	{
		return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	}
	return S_OK;
}

void AudioManager::Play(const char cue[])
{
	if (sound == NULL) return;
	cueI = sound->GetCueIndex(cue);
	sound->Play(cueI, 0, 0, NULL);
	//GameManager::print("사운드 재생 : %s\n", cue);
}

void AudioManager::Stop(const char cue[])
{
	if (sound == NULL) return;
	cueI = sound->GetCueIndex(cue);
	sound->Stop(cueI, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE);
	//GameManager::print("사운드 정지 : %s\n", cue);
}

void AudioManager::Update()
{
	if (engine == NULL) return;
	engine->DoWork();
}