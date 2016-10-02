#pragma once
class Monster : public Object
{
public:
	Monster(string name, D3DXVECTOR3 pos, float speed, int hp, int dmg, wstring sprite, string music = "N/A");
	//하스스톤으로 치면 전투의 함성같은 녀석
	virtual void InitMonster();
	//하스스톤으로 치면 죽음의 메아리같은 녀석
	virtual void DeleteMonster();
	virtual ~Monster();

public:
	virtual HRESULT Load() override;
	virtual void Update() override;
	virtual void Render() override;
	CharacterInfo* GetInfo()
	{
		return info;
	}
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

public:
	string MusicName = "N/A";
	wstring SpriteName = L"N/A";
	bool IsMove = true;
	D3DXVECTOR3 Destination;

protected:
	SpriteRenderer *renderer;
	CharacterInfo *info;
};