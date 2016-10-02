#include "DXUT.h"
#include "GameManager.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include <conio.h>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialize()
{
	mPlayerPtr = new Player();
	mPlayerPtr->Load();
	mItemPtr = new Item();
	mItemPtr->Load();
	mBossPtr = new Monster("Boss", D3DXVECTOR3(ClientRect.right/2.0f, ClientRect.bottom/2.0f, 0.0f), 0.5f, 22, 1, L"Resources/Debug/player.png", "YukiOnna00");
	mBossPtr->Load();

	print("start : %.2f\n", mPlayerPtr->info->Speed);
}

void GameManager::AudioInitialize()
{
	mAudioMngPtr = new AudioManager();
	mAudioMngPtr->initAudio();

#if DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif
}

HRESULT GameManager::Reset()
{
	HRESULT hr;
	V_RETURN(Renderer::CreateSprite());
	return S_OK;
}

void GameManager::OnLostDevice()
{
	Renderer::Release();
}

void GameManager::Update()
{
	ClientRect = DXUTGetWindowClientRect();

	mPlayerPtr->Update();
	mItemPtr->Update();
	mAudioMngPtr->Update();
	mBossPtr->Update();
	if (mPBptr != nullptr) mPBptr->Update();

	if (IsTriggerOn(mPlayerPtr->GetRect(), mItemPtr->GetRect()))
	{
		print("플레이어와 아이템 충돌함\n");
		mItemPtr->Respawn();
		mPlayerPtr->info->Speed+=0.22f;
		mBossPtr->GetInfo()->Speed *= 1.5;
		mBossPtr->GetInfo()->DMG += 1;
		print("현재 속도 : %.2f\n", mPlayerPtr->info->Speed);
		if (mPlayerPtr->info->Speed > 22)
		{
			GameOver();
		}
	}
	if (IsTriggerOn(mBossPtr->GetRect(), mPlayerPtr->GetRect()))
	{
		print("보스와 플레이어 충돌함\n");
		mPlayerPtr->info->NowHP -= mBossPtr->GetInfo()->DMG;
		print("현재 체력 : %d\n", mPlayerPtr->info->NowHP);
		mPlayerPtr->Respawn();
		if (mPlayerPtr->info->NowHP <= 0)
		{
			GameOver();
		}
	}
	if (mPBptr != nullptr)
	{
		if (IsTriggerOn(mBossPtr->GetRect(), mPBptr->GetRect()))
		{
			print("보스와 탄환 충돌함\n");
			mBossPtr->GetInfo()->NowHP -= mPlayerPtr->info->DMG;
			print("보스 체력 : %d\n", mBossPtr->GetInfo()->NowHP);
			mPBptr->Shoot(D3DXVECTOR3(ClientRect.right*2, ClientRect.bottom*2, 0), Up);
			if (mBossPtr->GetInfo()->NowHP <= 0)
			{
				mBossPtr->~Monster();
				GameOver();
			}
		}
	}
}

void GameManager::GameOver()
{
	mPlayerPtr->~Player();
	mItemPtr->~Item();
	mBossPtr->~Monster();
	if (mPBptr != nullptr) mPBptr->~Bullet();
	print("Game Over\n");
	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE) & 0x8000 || GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			DXUTShutdown();
			return;
		}
	}
}

void GameManager::Render()
{
	mPlayerPtr->Render();
	mItemPtr->Render();
	mBossPtr->Render();
	if (mPBptr != nullptr) mPBptr->Render();
}

void GameManager::Destroy()
{
	SAFE_DELETE(mPlayerPtr);
	SAFE_DELETE(mItemPtr);
	SAFE_DELETE(mBossPtr);
	SAFE_DELETE(mAudioMngPtr);
	SAFE_DELETE(mPBptr);
#if DEBUG
	FreeConsole();
#endif
	Renderer::Release();
}

//렉트 두 개를 인자로 받아 충돌체크를 한다
bool GameManager::IsTriggerOn(const RECT& a, const RECT& b)
{
	return (a.left <= b.right && a.right >= b.left && a.top <= b.bottom && a.bottom >= b.top);
}