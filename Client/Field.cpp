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


#include "Obj.h"

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
#include "BasicStore.h"
#include "BasicStoreBridge.h"
#include "DrugStore.h"
#include "DrugStoreBridge.h"
#include "MercenaryStore.h"
#include "MercenaryStoreBridge.h"

#include "MercenaryDisplay.h"
#include "MercenaryDisplayBridge.h"

#include "TownButton.h"
#include "TownBridge.h"



CField::CField(void)
: m_bStage(false)
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
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"GoniSh", L"Walk_1", D3DXVECTOR3(500.f, 200.f, 0.f)));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"DocuGawa", L"Walk_1", D3DXVECTOR3(200.f, 300.f, 0.f)));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"BlueDragon", L"Walk_1", D3DXVECTOR3(600.f, 100.f, 0.f)));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"HonGanji", L"Walk_1", D3DXVECTOR3(1200.f, 400.f, 0.f)));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"KimYuSin", L"Walk_1", D3DXVECTOR3(1500.f, 700.f, 0.f)));
	CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CEnemyUnit, CEnemyBridge>::CreateObj(L"Waki", L"Walk_1", D3DXVECTOR3(900.f, 300.f, 0.f)));

	


	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"FieldMainUi",400.f,553.f));	
	CUIMgr::GetInstance()->AddUI(UI_INVEN, CUIFactory<CInventory,CInvenBridge>::CreateUI(L"Inventory", 580.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STAT, CUIFactory<CStatus,CStatusBridge>::CreateUI(L"Status", 180.f, 250.f));

	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CBasicStore,CBasicStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CDrugStore,CDrugStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CMercenaryStore,CMercenaryStoreBridge>::CreateUI(L"Store",200.f,250.f));

	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CTownButton,CTownBridge>::CreateUI(L"BigTown", 1720.f, 320.f));

	return S_OK;	

}

void	CField::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Picking();
	CObjMgr::GetInstance()->Picking();
	

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

	/*if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Tile/Tile/Tile%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 216)))
	{
		ERR_MSG(L"Tile 멀티 텍스쳐 생성 실패")
		return;
	}*/

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/TILEMAP/TILE0%d.png", 
		L"TILE", TEX_MULTI, L"Tile", 4)))
	{
		ERR_MSG(L"TILE 멀티 텍스쳐 생성 실패")
		return;
	}
	
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
	/////////////////////////////////////////////////용병창 테스트
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Portrait/ArcherK/UI1.png", 
		L"TestUnit", TEX_SINGLE)))
	{
		ERR_MSG(L"TestUnit 싱글 텍스쳐 생성 실패");
		return;
	}
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Portrait/ArcherK/UI0.png", 
		L"TestUnit2", TEX_SINGLE)))
	{
		ERR_MSG(L"TestUnit 싱글 텍스쳐 생성 실패");
		return;
	}



	/////////////////////////////////////////툴팁버튼
	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownButton/UI0.png", 
		L"StoreButton", TEX_SINGLE)))
	{
		ERR_MSG(L"TestUnit 싱글 텍스쳐 생성 실패");
		return;
	}
	// 마을 버튼 - 은지 추가
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Town/Big/Town%d.png", 
		L"BIGTOWN", TEX_MULTI, L"BigTown", 2)))
	{
		ERR_MSG(L"BIGTOWN 멀티 텍스쳐 생성 실패")
		return;
	}


}