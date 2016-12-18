#include "StdAfx.h"
#include "MercenaryStore.h"
#include "KeyMgr.h"

CMercenaryStore::CMercenaryStore(void)
{
}

CMercenaryStore::~CMercenaryStore(void)
{
}

HRESULT	CMercenaryStore::Initialize(void)
{
	//m_wstrObjKey = L"Inventory";	

	return S_OK;
}

void	CMercenaryStore::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown('M'))
	{

		if (m_bView == true)
			m_bView = false;
		else
			m_bView = true;

	}

	if (m_bView)
		m_pBridge->Progress(m_tInfo);	

}

void	CMercenaryStore::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CMercenaryStore::Release(void)
{
	::Safe_Delete(m_pBridge);
}
