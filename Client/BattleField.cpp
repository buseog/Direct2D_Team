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
	CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");

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
		ERR_MSG(L"Tile 멀티 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI0.png", 
		L"MainUI", TEX_SINGLE)))
	{
		ERR_MSG(L"MainUI 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI20.png", 
		L"Inventory", TEX_SINGLE)))
	{
		ERR_MSG(L"Inventory 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Weapon/0.png", 
		L"Weapon", TEX_SINGLE)))
	{
		ERR_MSG(L"Weapon 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Armor/8.png", 
		L"Armor", TEX_SINGLE)))
	{
		ERR_MSG(L"Armor 싱글 텍스쳐 생성 실패")
		return;
	}


	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI21.png", 
		L"Status", TEX_SINGLE)))
	{
		ERR_MSG(L"Status 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/UI7.png", 
		L"Store", TEX_SINGLE)))
	{
		ERR_MSG(L"Store 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/UI10.png", 
		L"ToolTip", TEX_SINGLE)))
	{
		ERR_MSG(L"Store 싱글 텍스쳐 생성 실패")
		return;
	}


	///아이템테스트
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Weapon/0.png", 
		L"TestWeapon", TEX_SINGLE)))
	{
		ERR_MSG(L"TestArmor 싱글 텍스쳐 생성 실패")
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Armor/0.png", 
		L"TestArmor", TEX_SINGLE)))
	{
		ERR_MSG(L"TestArmor 싱글 텍스쳐 생성 실패")
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Glove/0.png", 
		L"TestGlove", TEX_SINGLE)))
	{
		ERR_MSG(L"TestGlove 싱글 텍스쳐 생성 실패")
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Helmet/0.png", 
		L"TestHelmet", TEX_SINGLE)))
	{
		ERR_MSG(L"TestArmor 싱글 텍스쳐 생성 실패");
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Shoes/0.png", 
		L"TestBoots", TEX_SINGLE)))
	{
		ERR_MSG(L"TestArmor 싱글 텍스쳐 생성 실패")
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Belt/0.png", 
		L"TestBelt", TEX_SINGLE)))
	{
		ERR_MSG(L"TestArmor 싱글 텍스쳐 생성 실패")
		return;
	}
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Item/Food/2.png", 
		L"TestFood", TEX_SINGLE)))
	{
		ERR_MSG(L"TestFood 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/SelectEffect/SelectEffect.png", 
		L"SelectEffect", TEX_SINGLE)))
	{
		ERR_MSG(L"SelectEffect 싱글 텍스쳐 생성 실패")
		return;
	}

	/////////////스텟 창 테스트 /////////////////////////////
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI15.png", 
		L"Button", TEX_SINGLE)))
	{
		ERR_MSG(L"Button 싱글 텍스쳐 생성 실패");
		return;
	}


}