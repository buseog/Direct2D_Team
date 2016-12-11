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
	LPDIRECT3DTEXTURE9		pTexture;	// 이미지 한 장을 보관하기 위한 컴객체, 이미지의 실제적인 정보
	D3DXIMAGE_INFO			tImgInfo;	// 이미지 정보를 보관하기 위한 구조체, 이미지 외부 정보를 담는다.

}TEXINFO;

// 툴에서 사용할 타일.
typedef struct tagToolTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;
}TILE;

// 클라에서 사용될타일. AStar용 인접리스트 가지고있음
typedef struct tagClilTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;
	list<int>			Connectlist;

}TILE2;

// 이전툴에서 쓰던 타일돌리는 구조체
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

// 이전툴에서 쓰던 유닛데이터 삭제예정
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

// 경로 저장하기위한 구조체
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

// 스프라이트 돌릴 구조체
typedef struct tagFrame
{
	float		fFrame;
	float		fCount;
	float		fMax;

	tagFrame(void){}
	tagFrame(float _fFrame, float _fCount, float _fMax)
		: fFrame(_fFrame), fCount(_fCount), fMax(_fMax)
	{

	}

}FRAME;


// AStar 리스트 노드
typedef	struct tagAStarNode
{
	float				fCost;
	int					iIndex;
	tagAStarNode*		pParent;

}NODE;

// 유닛 스텟
typedef struct tagStatus
{
	wstring		strName;
	int			iHp;
	int			iMp;
	int			iLevel;
	int			iExp;
	int			iStr;
	int			iDex;
	int			iInt;
	int			iAttack;
	int			iDef;
	float		fMoveSpeed;
	float		fAttackSpeed;
}STAT;

// 마을툴에서 사용하는 구조체
typedef struct tagStore
{
	wstring			wstrName;	
	D3DXVECTOR3			vPos;
	CImage			pngImage;


}STORE;

// 아이템 구조체
typedef struct tagItem
{
	wstring			wstrName;
	D3DXVECTOR3		vPos;
	int				iOption;
	int				iWeight;
	int				iPrice;
	ITEMID			eType;
}ITEM;

// UI	구조체(?)
typedef struct tagUIData
{

	int		iLevel;
	int		iAttack;


}DATA;