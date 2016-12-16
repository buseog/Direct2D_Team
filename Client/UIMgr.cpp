#include "StdAfx.h"
#include "UIMgr.h"
#include "Ui.h"
#include "MainUiBridge.h"
#include "InvenBridge.h"
#include "UIFactory.h"
#include "MainUi.h"
#include "Inventory.h"
#include "Back.h"
#include "Status.h"
#include "StatusBridge.h"
#include "Store.h"
#include "StoreBridge.h"

IMPLEMENT_SINGLETON(CUIMgr)

CUIMgr::CUIMgr(void)
{
}

CUIMgr::~CUIMgr(void)
{
	Release();
}

void CUIMgr::AddUI(UIID eUiID, CUi* pUi)
{
	m_UiList[m_eSceneID][eUiID].push_back(pUi);
}

HRESULT	CUIMgr::Initialize(void)
{
	m_UiList[m_eSceneID][UI_MAIN].push_back(CUIFactory<CMainUi,CMainUiBridge>::CreateUI(L"MainUI",400.f,553.f));
		
	m_UiList[m_eSceneID][UI_INVEN].push_back(CUIFactory<CInventory,CInvenBridge>::CreateUI(L"Inventory", 580.f,250.f));

	m_UiList[m_eSceneID][UI_STAT].push_back(CUIFactory<CStatus,CStatusBridge>::CreateUI(L"Status", 180.f, 250.f));

	m_UiList[m_eSceneID][UI_STORE].push_back(CUIFactory<CStore,CStoreBridge>::CreateUI(L"Store", 180.f,250.f));


	return S_OK;
}

void CUIMgr::Progress(void)
{
	for(size_t i = 0; i < UI_END; ++i)
	{
		for(list<CUi*>::iterator	iter = m_UiList[m_eSceneID][i].begin();
			iter != m_UiList[m_eSceneID][i].end(); ++iter)
		{
			(*iter)->Progress();
		}
	}


}

void CUIMgr::Render(void)
{
	for(size_t i = 0; i < UI_END; ++i)
	{
		for(list<CUi*>::iterator	iter = m_UiList[m_eSceneID][i].begin();
			iter != m_UiList[m_eSceneID][i].end(); ++iter)
		{
			(*iter)->Render();
		}
	}

}

void CUIMgr::Release()
{
	for (int id = 0; id < SC_END; ++id)
	{
		for(size_t i = 0; i < UI_END; ++i)
		{
			for(list<CUi*>::iterator	iter = m_UiList[id][i].begin();
				iter != m_UiList[id][i].end(); ++iter)
			{
				::Safe_Delete(*iter);
			}
			m_UiList[id][i].clear();
		}
	}
}

void CUIMgr::SetSceneID(SCENEID	eID)
{
	m_eSceneID = eID;
}

void CUIMgr::AddSorting(CUi*	pUi)
{
	m_mapUiRender.insert(map<int, CUi*>::value_type());
}

void CUIMgr::MapClear(void)
{
	m_mapUiRender.clear();
}