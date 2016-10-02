#pragma once
#include "Singleton.h"
#include "Object.h"
#include "AudioManager.h"
#include "Player.h"
#include "Item.h"
#include "Monster.h"
#include "Bullet.h"

class Player;
class Item;
class Monster;
class Bullet;

struct CharacterInfo
{
	string Name;
	float Speed;
	int MaxHP, NowHP;
	int DMG;
};

enum Rotate
{
	Left = 0,
	Right,
	Up,
	Down,
};

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	virtual ~GameManager();
	
public:
	void Initialize();
	void AudioInitialize();
	HRESULT Reset();
	void OnLostDevice();
	void Update();
	void Render();
	void Destroy();
	void GameOver();
	bool IsTriggerOn(const RECT& a, const RECT& b);
	static int print(_In_z_ _Printf_format_string_ char const* const _Format, ...)
	{
#if DEBUG
		va_list arg;
		int cnt = 0;

		va_start(arg, _Format);
		cnt = vprintf(_Format, arg);
		va_end(arg);

		return cnt;
#else
		return NULL;
#endif
	}

public:
	Player *mPlayerPtr;
	Item *mItemPtr;
	AudioManager *mAudioMngPtr;
	RECT ClientRect;
	const char *NowPlaying;
	Monster *mBossPtr;
	Bullet *mPBptr;
};