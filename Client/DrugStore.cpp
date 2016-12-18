#include "StdAfx.h"
#include "DrugStore.h"
#include "KeyMgr.h"

CDrugStore::CDrugStore(void)
{
}

CDrugStore::~CDrugStore(void)
{
}

HRESULT	CDrugStore::Initialize(void)
{
	//m_wstrObjKey = L"Inventory";	

	return S_OK;
}

void	CDrugStore::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown('N'))
	{

		if (m_bView == true)
			m_bView = false;
		else
			m_bView = true;

		m_pBridge->Render();
	}

	if (m_bView)
		m_pBridge->Progress(m_tInfo);	

}

void	CDrugStore::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CDrugStore::Release(void)
{
	::Safe_Delete(m_pBridge);
}
