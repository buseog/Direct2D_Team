#include "StdAfx.h"
#include "BattleField.h"

#include "ObjMgr.h"
#include "UiMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "CrowdMgr.h"

#include "ObjFactory.h"
#include "UIFactory.h"

#include "Obj.h"
#include "Back.h"
#include "BattleFieldBackBridge.h"

#include "AllyUnit.h"

#include "ShortAttack.h"
#include "ShortAttackBridge.h"
#include "LongAttack.h"
#include "LongAttackBridge.h"

#include "UnitBridge.h"
#include "CollisionMgr.h"


#include "MainUi.h"
#include "MainUiBridge.h"

#include "Player.h"
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

	CObjMgr::GetInstance()->AddObject(OBJ_BACK, CObjFactory<CBack, CBattleFieldBackBridge>::CreateObj(L"BattleField", 0, 0));
	CObjMgr::GetInstance()->AddObject(OBJ_UNIT, CObjFactory<CAllyUnit, CUnitBridge>::CreateObj(L"YiSunshin", L"Walk_1", D3DXVECTOR3(300.f, 300.f, 0.f)));

	for(int i = 0; i < 3; ++i)
	{
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CShortAttack, CShortAttackBridge>::CreateObj(L"DocuGawa", L"Walk_1", 
					D3DXVECTOR3(1700.f + (i*100), 100.f  + (i*30), 0.f)));
	}
	for(int i = 0; i< 2; ++ i)
	{	
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CShortAttack, CShortAttackBridge>::CreateObj(L"DocuGawa", L"Walk_1", 
					D3DXVECTOR3(1800.f + (i*120), 70.f  + (i*30), 0.f)));
	}

	for(int i = 0; i < 3; ++i )
	{
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CLongAttack, CLongAttackBridge>::CreateObj(L"Waki", L"Walk_1", 
					D3DXVECTOR3(1800.f + (i*120), 500.f  - (i*30), 0.f)));
	}

	for(int i = 0; i < 2; ++i )
	{
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CLongAttack, CLongAttackBridge>::CreateObj(L"Waki", L"Walk_1", 
					D3DXVECTOR3(1850.f + (i*120), 450.f  - (i*30), 0.f)));
	}

	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi, CMainUiBridge>::CreateUI(L"Minimap", 100.f, 550.f));	
	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi, CMainUiBridge>::CreateUI(L"BattleFieldMainUi",400.f,553.f));	
	return S_OK;
}

void	CBattleField::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
	CObjMgr::GetInstance()->Picking();
	

}

void	CBattleField::Render(void)
{
	CObjMgr::GetInstance()->Render();
	CUIMgr::GetInstance()->Render();
	CCrowdMgr::GetInstance()->RenderPortrait();
}

void	CBattleField::Release(void)
{


}

void	CBattleField::LoadPNG(void)
{
	
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map01.png", L"BattleField", TEX_SINGLE)))
	{
		ERR_MSG (L"BattleField 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map03.png", L"Minimap", TEX_SINGLE)))
	{
		ERR_MSG (L"Minimap 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/SelectEffect/SelectEffect.png", L"SelectEffect", TEX_SINGLE)))
	{
		ERR_MSG(L"SelectEffect 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI1.png", L"BattleFieldMainUi", TEX_SINGLE)))
	{
		ERR_MSG(L"MainUI 싱글 텍스쳐 생성 실패")
		return;

	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI4.png", L"BattlePannel", TEX_SINGLE)))
	{
		ERR_MSG (L"BattlePannel 싱글 텍스쳐 생성 실패")
		return;
	}

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

	// 단축키 버튼 (은지 추가)
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI2.png", L"HotKeyStop", TEX_SINGLE)))
	{
		ERR_MSG (L"HotKeyStop 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI3.png", L"HotKeyAttack", TEX_SINGLE)))
	{
		ERR_MSG (L"HotKeyAttack 싱글 텍스쳐 생성 실패")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/CharInfo/UI4.png", L"HotKeyMove", TEX_SINGLE)))
	{
		ERR_MSG (L"HotKeyMove 싱글 텍스쳐 생성 실패")
		return;
	}


}