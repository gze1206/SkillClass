#pragma once

class Bullet : public Object
{
public:
	Bullet(D3DXVECTOR3 pos, Rotate rot);
	virtual ~Bullet();

public:
	virtual void Render() override;
	virtual HRESULT Load() override;
	virtual void Update() override;

	void Shoot(D3DXVECTOR3 pos, Rotate rot);

	SpriteRenderer *renderer;
	RECT rc;

public:
	float Speed = 1.0f;
	Rotate rotate;
};

