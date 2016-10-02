/*
Copyright (c) 2011 by Chrles Kelly
C++와 DirectX로 게임 엔진을 제작하며 배우는 2D 게임 프로그래밍 참고
*/

#pragma once
#include <xact3.h>

class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();
	HRESULT initAudio();
	void Update();
	void Play(const char cue[]);
	void Stop(const char cue[]);

private:
	IXACT3Engine *engine;
	IXACT3WaveBank *wave;
	IXACT3SoundBank *sound;
	XACTINDEX cueI;
	void *mapWaveBank;
	void *soundBankData;
	bool initialized;
};

