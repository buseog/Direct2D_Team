#include "StdAfx.h"
#include "InVillage.h"
#include "ObjFactory.h"
#include "UIFactory.h"
#include "InVillageBackBridge.h"
#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Back.h"

#include "Inventory.h"
#include "InvenBridge.h"

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

#include "MainUi.h"
#include "MainUiBridge.h"

CInVillage::CInVillage(void)
{
}

CInVillage::~CInVillage(void)
{
}

HRESULT	CInVillage::Initialize(void)
{
	LoadPNG();

	CObjMgr::GetInstance()->AddObject(OBJ_BACK, CObjFactory<CBack, CInVillageBackBridge>::CreateObj(L"InVillage", 0, 0));
	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"FieldMainUi",400.f,553.f));	

	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CBasicStore,CBasicStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CDrugStore,CDrugStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CMercenaryStore,CMercenaryStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CMercenaryDisplay,CMercenaryDisplayBridge>::CreateUI(L"Store",0.f,250.f));
	//CUIMgr::GetInstance()->AddUI(UI_INVEN, CUIFactory<CInventory,CInvenBridge>::CreateUI(L"Inventory", 580.f,250.f));
	// 인벤에서 터져서 막아놓음



	/*CObjMgr::GetInstance()->AddObject(OBJ_BACK, CObjFactory<CBack, CVillageBackBridge>::CreateObj(L"Village", 0, 0));
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CBasicTownButton,CBasicBridge>::CreateUI(L"Drug", 400.f, 250.f));
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CDrugTownButton,CDrugBridge>::CreateUI(L"Basic", 200.f, 390.f));
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CMercenaryTownButton,CMercenaryBridge>::CreateUI(L"Mercenary", 650.f, 400.f));

	CSoundMgr::GetInstance()->SoundStop(0);

	CSoundMgr::GetInstance()->SoundPlay(2, 0);*/

	return S_OK;
}

void	CInVillage::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Picking();
	CObjMgr::GetInstance()->Picking();
	
}
void	CInVillage::Render(void)
{
	CObjMgr::GetInstance()->Render();
 	CUIMgr::GetInstance()->Render();
}

void	CInVillage::Release(void)
{
	
}

void	CInVillage::LoadPNG(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/UI5.png", L"InVillage", TEX_SINGLE)))
	{
		ERR_MSG (L"InVillage 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/Tooltip1.png", L"Tooltip1", TEX_SINGLE)))
	{
		ERR_MSG (L"Tooltip1 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/Tooltip2.png", L"Tooltip2", TEX_SINGLE)))
	{
		ERR_MSG (L"Tooltip2 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/TownBack/Tooltip3.png", L"Tooltip3", TEX_SINGLE)))
	{
		ERR_MSG (L"Tooltip3 싱글 텍스쳐 생성 실패")
		return;
	}
}