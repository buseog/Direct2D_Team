#include "StdAfx.h"
#include "BattleField.h"
#include "ObjMgr.h"
#include "CrowdMgr.h"
#include "UIMgr.h"

CBattleField::CBattleField(void)
{
}

CBattleField::~CBattleField(void)
{
}

HRESULT	CBattleField::Initialize(void)
{
	LoadPNG();

	return S_OK;
}

void	CBattleField::Progress(void)
{
	CCrowdMgr::GetInstance()->Progress();
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
}

void	CBattleField::Render(void)
{
	CObjMgr::GetInstance()->Render();
 	CUIMgr::GetInstance()->Render();
}

void	CBattleField::Release(void)
{
	

}

void	CBattleField::LoadPNG(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile/Tile%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 216)))
	{
		ERR_MSG(L"Tile ��Ƽ �ؽ��� ���� ����");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI0.png", 
		L"MainUI", TEX_SINGLE)))
	{
		ERR_MSG(L"MainUI �̱� �ؽ��� ���� ����");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI20.png", 
		L"Inventory", TEX_SINGLE)))
	{
		ERR_MSG(L"Inventory �̱� �ؽ��� ���� ����");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI21.png", 
		L"Status", TEX_SINGLE)))
	{
		ERR_MSG(L"Status �̱� �ؽ��� ���� ����");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/SelectEffect/SelectEffect.png", 
		L"SelectEffect", TEX_SINGLE)))
	{
		ERR_MSG(L"SelectEffect �̱� �ؽ��� ���� ����");
		return;
	}

	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/PlayerPath.txt");
	CTextureMgr::GetInstance()->ReadImgPath(L"../Data/EffectPath.txt");
}