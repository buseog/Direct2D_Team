#include "StdAfx.h"
#include "Village.h"
#include "ObjMgr.h"
#include "UiFactory.h"
#include "UiMgr.h"
#include "ObjFactory.h"
#include "VillageBackBridge.h"
#include "Back.h"
#include "MainUi.h"
#include "MainUiBridge.h"

#include "BasicTownButton.h"
#include "BasicBridge.h"

#include "DrugTownButton.h"
#include "DrugBridge.h"

#include "MercenaryTownButton.h"
#include "MercenaryBridge.h"

#include "SoundMgr.h"

CVillage::CVillage(void)
{
}

CVillage::~CVillage(void)
{
	Release();
}

HRESULT	CVillage::Initialize(void)
{
	LoadPNG();
	CUIMgr::GetInstance()->AddUI(UI_MAIN, CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"FieldMainUi",400.f,553.f));	

	// ���� ���
	CObjMgr::GetInstance()->AddObject(OBJ_BACK, CObjFactory<CBack, CVillageBackBridge>::CreateObj(L"Village", 0, 0));

	// ���ʻ���
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CBasicTownButton,CBasicBridge>::CreateUI(L"Drug", 400.f, 250.f));

	// ������
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CDrugTownButton,CDrugBridge>::CreateUI(L"Basic", 200.f, 390.f));

	// �뺴����
	CUIMgr::GetInstance()->AddUI(UI_BUTTON, CUIFactory<CMercenaryTownButton,CMercenaryBridge>::CreateUI(L"Mercenary", 650.f, 400.f));

	CSoundMgr::GetInstance()->SoundStop(0);

	CSoundMgr::GetInstance()->SoundPlay(2, 0);

	return S_OK;
}

void	CVillage::Progress(void)
{
	CObjMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Progress();
	CUIMgr::GetInstance()->Picking();
}

void	CVillage::Render(void)
{
	CObjMgr::GetInstance()->Render();
 	CUIMgr::GetInstance()->Render();
}

void	CVillage::Release(void)
{
	
}

void	CVillage::LoadPNG(void)
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map02.png", L"Village", TEX_SINGLE)))
	{
		ERR_MSG (L"Village �̱� �ؽ��� ���� ����")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Town/Clinic/Town%d.png", 
		L"DRUG", TEX_MULTI, L"Drug", 3)))
	{
		ERR_MSG(L"DRUG ��Ƽ �ؽ��� ���� ����")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Town/WStore/Town%d.png", 
		L"BASIC", TEX_MULTI, L"Basic", 3)))
	{
		ERR_MSG(L"BASIC ��Ƽ �ؽ��� ���� ����")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Town/GBarrack/Town%d.png", 
		L"MERCENARY", TEX_MULTI, L"Mercenary", 3)))
	{
		ERR_MSG(L"MERCENARY ��Ƽ �ؽ��� ���� ����")
		return;
	}

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/UI/Pannel/UI0.png", 
		L"FieldMainUi", TEX_SINGLE)))
	{
		ERR_MSG(L"MainUI �̱� �ؽ��� ���� ����")
		return;
	}
}