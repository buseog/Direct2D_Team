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

// ������ ����� Ÿ��.
typedef struct tagToolTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;
}TILE;

// Ŭ�󿡼� ����Ÿ��. AStar�� ��������Ʈ ����������
typedef struct tagClilTile
{
	D3DXVECTOR3			vPos;
	D3DXVECTOR3			vSize;
	BYTE				byOption;
	BYTE				byDrawID;
	list<int>			Connectlist;

}TILE2;

// ���������� ���� Ÿ�ϵ����� ����ü
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

// ���� ���� ����ü
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


	BOOL bCaravan; //�������� ���� 2��
	BOOL bRapidAttack;//����2��
	BOOL bRapidMoveSpeed;//�̼�2��
	BOOL bHardSkin;//����2��
	BOOL bBadassDMG;//���ݷ�2��
	BOOL bTank;//ü��2��
	UINT UnitType;
}DETAILDATA;

// ���� ���� ����Ÿ
typedef struct tagUnitData
{
	//CString strName;
	wstring	wstrName;
	int iAttack;
	int iDeffence;
	int iHealthPoint;
	float fAttackSpeed;
	float fMoveSpeed;
	float fRange;
	DETAILDATA tDetail;


}UNITDATA;

// ��� �����ϱ����� ����ü
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

// ��������Ʈ ���� ����ü
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


// AStar ����Ʈ ���
typedef	struct tagAStarNode
{
	float				fCost;
	int					iIndex;
	tagAStarNode*		pParent;

}NODE;

// ���� ����
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

// ���������� ����ϴ� ����ü
typedef struct tagStore
{
	wstring			wstrName;	
	D3DXVECTOR3			vPos;
	CImage			pngImage;


}STORE;

// ������ ����ü
typedef struct tagItem
{
	wstring			wstrName;
	D3DXVECTOR3		vPos;
	int				iOption;
	int				iWeight;
	int				iPrice;
	ITEMID			eType;
}ITEM;

typedef struct tagKey
{
	CString		m_ObjKey;
	CString		m_StateKey;
}KEY;

