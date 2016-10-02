#include "DXUT.h"
#include "Renderer.h"

LPD3DXSPRITE Renderer::sD3DxSpritePtr;

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Release()
{
	SAFE_RELEASE(sD3DxSpritePtr);
}

HRESULT Renderer::CreateSprite()
{
	HRESULT hr;
	V_RETURN(D3DXCreateSprite(DXUTGetD3D9Device(), &sD3DxSpritePtr));
	return S_OK;
}

void Renderer::SetTexture(shared_ptr<Texture> texture)
{
	mTexturePtr = texture;
}