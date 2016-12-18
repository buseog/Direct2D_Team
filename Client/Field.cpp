#include "StdAfx.h"
#include "Field.h"

#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "ObjFactory.h"
#include "UIFactory.h"

#include "Back.h"
#include "FieldBackBridge.h"
#include "Player.h"
#include "PlayerBridge.h"

#include "EnemyUnit.h"
#include "EnemyBridge.h"

#include "MainUi.h"
#include "MainUiBridge.h"
#include "Inventory.h"
#include "InvenBridge.h"
#include "Status.h"
#include "StatusBridge.h"
#include "Store.h"
#include "StoreBridge.h"

CField::CField(void)
{
}

CField::~CField(void)
{
	Release();
}

HRESULT	CField::Initialize(void)
{
	LoadPNG();
	CSceneMgr::GetInstance()->SetMouse(L"Hand_Stand");

	CObjMgr::GetInstance()->AddObject(OBJ_BACK, CObjFactory<CBack, CFieldBackBridge>::CreateObj(L"Field", 0, 0));
	CObjMgr::GetInstance()->AddObject(OBJ_PLAYER, CObjFactory<CPlayer, CPlayerBridge>::CreateObj(L"Walk_1", 300.f, 300.f));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"GoniSh", L"Walk_1", D3DXVECTOR3(400.f, 300.f, 0.f)));



	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"FieldMainUi",400.f,553.f));	
	CUIMgr::GetInstance()->AddUI(UI_INVEN, CUIFactory<CInventory,CInvenBridge>::CreateUI(L"Inventory", 580.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STAT, CUIFactory<CStatus,CStatusBridge>::CreateUI(L"Status", 180.f, 250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CStore,CStoreBridge>::CreateUI(L"Store", 180.f,250.f));



	return S_OK;
}

void	CField::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();

	if (CKeyMgr::GetInstance()->KeyDown(VK_RETURN))
		CSceneMgr::GetInstance()->SetScene(SC_BATTLEFIELD);
}

void	CField::Render(void)
{
	CObjMgr::GetInstance()->Render();
	CUIMgr::GetInstance()->Render();
}

void	CField::Release(void)
{

}

void	CField::LoadPNG(void)
{
	CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map00.png", L"Field", TEX_SINGLE);

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile/Tile%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 216)))
	{
		ERR_MSG(L"Tile 멀티 텍스쳐 생성 실패")
		return;
	}
	
	

	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/EnemyUnit/Gonish/Walk_1/Gonish%d.png", 
		L"EnemyUnit", TEX_MULTI, L"GoniSh", 8)))
	{
		ERR_MSG(L"GoniSh 멀티 텍스쳐 생성 실패")
		return;
	}*/
	
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI0.png", 
		L"FieldMainUi", TEX_SINGLE)))
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

	/////////////스텟 창 테스트 /////////////////////////////
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI15.png", 
		L"Button", TEX_SINGLE)))
	{
		ERR_MSG(L"Button 싱글 텍스쳐 생성 실패");
		return;
	}
}