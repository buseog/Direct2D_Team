#include "StdAfx.h"
#include "BattleField.h"
#include "ObjMgr.h"
#include "CrowdMgr.h"

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
}

void	CBattleField::Render(void)
{
	CObjMgr::GetInstance()->Render();
}

void	CBattleField::Release(void)
{

}

void	CBattleField::LoadPNG(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 216)))
	{
		ERR_MSG(L"Tile 멀티 텍스쳐 생성 실패");
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Player/Walk_1/KimSimin%d.png", 
		L"PLAYER", TEX_MULTI, L"Walk_1", 8)))
	{
		ERR_MSG(L"Player 멀티 텍스쳐 생성 실패");
		return;
	}
}