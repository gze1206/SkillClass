#pragma once
#include <string>
using namespace std;

class Texture
{
public:
	Texture();
	Texture(wstring path);
	~Texture();

public:
	HRESULT Load(const wstring& path, UINT mipmap = 1);
	const LPDIRECT3DTEXTURE9& Get();
	const D3DXIMAGE_INFO& GetInfo();

private:
	LPDIRECT3DTEXTURE9 mTexture9Ptr;
	D3DXIMAGE_INFO mInfo;
};

