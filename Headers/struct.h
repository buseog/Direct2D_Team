#pragma once

using namespace std;
typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;

	D3DXMATRIX	matWorld;
	int			iCount;

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

// 지형 오브젝트 사용 시 필요한 정보
typedef	struct	tagBackObj
{
	D3DXVECTOR3			vPos;
	int					iIndex;
	CString				szState;
	CString				szObj;

}BACK;

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

// 현도 유닛 구조체
typedef struct tagUnitDataDetail
{
	int iLevel;
	int iStr;
	int iDex;
	int iVital;
	int iInt;

	int iExperience;
	int iBonusPoint;
	int iWeight;


	BOOL bCaravan; //소지가능 무게 2배
	BOOL bRapidAttack;//공속2배
	BOOL bRapidMoveSpeed;//이속2배
	BOOL bHardSkin;//방어력2배
	BOOL bBadassDMG;//공격력2배
	BOOL bTank;//체력2배
	UINT UnitType;
}DETAILDATA;

// 현도 유닛 데이타 (Stat 창에서 함께 씀)
typedef struct tagUnitData
{
	//CString strName;
	wstring	wstrName;

	int iAttack;
	int iDeffence;
	int iHealthPoint;
	int	iMaxHelathPoint; // 옵저버용 추가
	float fAttackSpeed;
	float fMoveSpeed;
	float fRange;
	DETAILDATA tDetail;


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
	int				iOption;
	int				iWeight;
	int				iPrice;
	int				iCount;
	ITEMID			eType;


}ITEM;

typedef struct tagKey
{
	CString		m_ObjKey;
	CString		m_StateKey;

}KEY;
