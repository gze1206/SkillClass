#pragma once
#include "Texture.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

public:
	static void Release();

public:
	virtual void SetTexture(shared_ptr<Texture> texture);
	virtual void Render() PURE;

	//sprite begin
public:
	static HRESULT CreateSprite();

public:
	static LPD3DXSPRITE sD3DxSpritePtr;

protected:
	shared_ptr<Texture> mTexturePtr;
};

