#include "StdAfx.h"
#include "Field.h"

#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

#include "ObjFactory.h"
#include "UIFactory.h"

#include "Obj.h"

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


#include "SoundMgr.h"

#include "AllyUnit.h"
#include "UnitBridge.h"
#include "ObjFactory.h"

#include "Back.h"
#include "FieldBackBridge.h"



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

	////////////
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CBasicStore,CBasicStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CDrugStore,CDrugStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CMercenaryStore,CMercenaryStoreBridge>::CreateUI(L"Store",200.f,250.f));
	CUIMgr::GetInstance()->AddUI(UI_STORE, CUIFactory<CMercenaryDisplay,CMercenaryDisplayBridge>::CreateUI(L"Store",0.f,250.f));
/////////////
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CTownButton,CTownBridge>::CreateUI(L"BigTown", 1720.f, 320.f));

	CSoundMgr::GetInstance()->LoadWave(L"../Sound/FieldBGM.wav");		// 필드 - 0
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Battleground.wav");	// 배틀존 - 1
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Town.wav");			// 마을 - 2
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/BuyItem.wav");		// 클릭 시 - 3
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/IceWall.wav");		// 아이스 월 - 4
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/storm.wav");			// 스톰 - 5
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/lightning.wav");		// 라이트닝 - 6
	CSoundMgr::GetInstance()->LoadWave(L"../Sound/Boom.wav");			// 폭발 - 7

	CSoundMgr::GetInstance()->SoundPlay(0, 1);

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

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI1.png", 
		L"HpBar", TEX_SINGLE)))
	{
		ERR_MSG(L"HpBar 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI12.png", 
		L"MpBar", TEX_SINGLE)))
	{
		ERR_MSG(L"MpBar 싱글 텍스쳐 생성 실패")
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

