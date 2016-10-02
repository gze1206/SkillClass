#include "DXUT.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Define.h"
#include <comdef.h>
#include <CRTDBG.H>
#include <atlconv.h>

Player::Player() : Object(), renderer(new SpriteRenderer()), info(new CharacterInfo{ "PLAYER", 3.0f, 10, 10, 1 }), rotate(Up)
{
	mPosition = D3DXVECTOR3(100, 100, 0);
	GameManager::print("플레이어 : %s 생성됨\n", info->Name.c_str());
	
	//GameError 테스트
	//try { throw(GameError(GameErrorDefine::FATAL_ERROR, "test")); }
	//catch (GameError ex)
	//{
	//	string temp = "";
	//	if (ex.GetCode() == -1) temp = "치명적인 오류!";
	//	MessageBoxA(DXUTGetHWND(), ex.GetErrorMessage(), temp.c_str(), NULL);
	//}
}


Player::~Player()
{
	GameManager::print("플레이어 : %s 제거됨\n", info->Name.c_str());
	SAFE_DELETE(info);
	SAFE_DELETE(renderer);
}

HRESULT Player::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/player.png"));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("플레이어 텍스쳐 로드됨\n");
	return S_OK;
}

void Player::Respawn()
{
	mPosition = D3DXVECTOR3(100, 100, 0);
	GameManager::print("플레이어 : %s 재생성됨\n", info->Name.c_str());
}

void Player::Update()
{
	if ((GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) && rc.top > GameManager::Get().ClientRect.top)
	{
		mPosition.y -= info->Speed;
		rotate = Up;
	}
	if ((GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState(VK_DOWN) & 0x8000) && rc.bottom < GameManager::Get().ClientRect.bottom)
	{
		mPosition.y += info->Speed;
		rotate = Down;
	}
	if ((GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState(VK_LEFT) & 0x8000) && rc.left > GameManager::Get().ClientRect.left)
	{
		mPosition.x -= info->Speed;
		rotate = Left;
	}
	if ((GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState(VK_RIGHT) & 0x8000) && rc.right < GameManager::Get().ClientRect.right)
	{
		mPosition.x += info->Speed;
		rotate = Right;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		(GameManager::Get().mPBptr == nullptr) ? GameManager::Get().mPBptr = new Bullet(mPosition, rotate) : GameManager::Get().mPBptr->Shoot(mPosition, rotate);
	}
}

void Player::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}