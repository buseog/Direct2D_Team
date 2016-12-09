#pragma once

using namespace std;
typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;

	D3DXMATRIX	matWorld;

}INFO;


typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9		pTexture;	// �̹��� �� ���� �����ϱ� ���� �İ�ü, �̹����� �������� ����
	D3DXIMAGE_INFO			tImgInfo;	// �̹��� ������ �����ϱ� ���� ����ü, �̹��� �ܺ� ������ ��´�.

}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;
	float				fAngle;
	float				fMirror;

}TILE;

typedef struct tagAction
{
	int iIndex;
	int iPrevdraw;
	int iPrevOption;
	int iAfterdraw;
	int	iAfterOption;

	tagAction ()
	{
	}
	tagAction (int _iIndex, int _iPrevdraw, int _iPrevOption, int _iAfterdraw, int _iAfterOption)
		:iIndex(_iIndex), iPrevdraw(_iPrevdraw), iPrevOption(_iPrevOption), iAfterdraw(_iAfterdraw), iAfterOption(_iAfterOption)
	{
	}
}TILE_ACTION;

typedef struct tagUnitData
{
	wstring			wstrName;
	float			fHp;
	float			fAttack;
	float			fAttackSpeed;
	float			fSpeed;
	int				iGold;

	BYTE			byOption;
	wstring			wstrImage;

}UNITDATA;

typedef	struct tagTexturePath
{
	wstring			wstrObjKey;
	wstring			wstrStateKey;
	wstring			wstrPath;
	int				iCount;

	tagTexturePath(void)
		: wstrObjKey(L""), wstrStateKey(L""), wstrPath(L""), iCount(0)
	{

	}
}IMGPATH;