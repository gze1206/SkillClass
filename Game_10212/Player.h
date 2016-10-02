#pragma once
#include "Object.h"
#include "Texture.h"
#include "Item.h"

class SpriteRenderer;
struct CharacterInfo;
enum Rotate;

class Player :
	public Object
{
public:
	Player();
	virtual ~Player();

public:
	virtual HRESULT Load() override;
	virtual void Update() override;
	virtual void Render() override;

	void SetInfo(CharacterInfo* InfoPtr)
	{
		info = InfoPtr;
	}

	void SwapInfo(CharacterInfo* InfoPtr)
	{
		CharacterInfo* temp = info;
		info = InfoPtr;
		InfoPtr = temp;
		SAFE_DELETE(temp);
	}

	void Respawn();

public:
	CharacterInfo *info;
	Rotate rotate;

protected:
	SpriteRenderer *renderer;
};

