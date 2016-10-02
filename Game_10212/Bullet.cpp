#include "DXUT.h"
#include "SpriteRenderer.h"
#include "Bullet.h"


Bullet::Bullet(D3DXVECTOR3 pos, Rotate rot) : Object(), renderer(new SpriteRenderer())
{
	Shoot(pos, rot);
	Load();
}


Bullet::~Bullet()
{
	SAFE_DELETE(renderer);
}

HRESULT Bullet::Load()
{
	HRESULT hr;
	mTexturePtr = make_shared<Texture>();
	V_RETURN(mTexturePtr->Load(L"Resources/Debug/e_bullet.png"));
	renderer->SetTexture(mTexturePtr);
	GameManager::print("ÅºÈ¯ ÅØ½ºÃÄ ·ÎµåµÊ\n");
	return S_OK;
}

void Bullet::Render()
{
	D3DXMatrixTranslation(&mWorldTM, mPosition.x, mPosition.y, mPosition.z);
	Renderer::sD3DxSpritePtr->SetTransform(&mWorldTM);
	renderer->Render();
}

void Bullet::Update()
{
	Speed = GameManager::Get().mPlayerPtr->info->Speed;
	if (rotate == Left)
	{
		mPosition.x -= Speed;
	}
	else if (rotate == Right)
	{
		mPosition.x += Speed;
	}
	else if (rotate == Up)
	{
		mPosition.y -= Speed;
	}
	else if (rotate == Down)
	{
		mPosition.y += Speed;
	}
}

void Bullet::Shoot(D3DXVECTOR3 pos, Rotate rot)
{
	mPosition = pos;
	rotate = rot;
}