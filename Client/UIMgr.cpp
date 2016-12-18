#include "StdAfx.h"
#include "UIMgr.h"
#include "Ui.h"



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
		for(int i = 0; i < UI_END; ++i)
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

int	CUIMgr::Picking(void)
{
	int iResult = -1;

	for(int i = 0; i < UI_END; ++i)
	{
		for(list<CUi*>::iterator	iter = m_UiList[m_eSceneID][i].begin();
			iter != m_UiList[m_eSceneID][i].end(); ++iter)
		{
			iResult = (*iter)->Picking();

			if (iResult > 0)
				return iResult;
		}
	}

	return iResult;
}