#pragma once
#include "Texture.h"

class Object
{
public:
	Object();
	virtual ~Object();

public:
	virtual HRESULT Load()
	{
		return S_OK;
	}

	virtual void Update()
	{

	}

	virtual void Render()
	{

	}

	const RECT& GetRect()
	{
		rc = { 0, 0, (LONG)mTexturePtr->GetInfo().Width, (LONG)mTexturePtr->GetInfo().Height };
		rc.top += mPosition.y;
		rc.left += mPosition.x;
		rc.bottom += mPosition.y;
		rc.right += mPosition.x;
		return rc;
	}

	D3DXVECTOR3 mPosition;

protected:
	D3DXMATRIX mWorldTM;
	RECT rc;
	shared_ptr<Texture> mTexturePtr;
};

