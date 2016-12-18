#include "StdAfx.h"
#include "Store.h"
//#include "Item.h"
#include "KeyMgr.h"

CStore::CStore(void)
{
}

CStore::~CStore(void)
{
	Release();
}


HRESULT	CStore::Initialize(void)
{
//	m_wstrObjKey = L"Inventory";	
		
	return S_OK;
}

void	CStore::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown('I'))
	{

		if (m_bView == true)
			m_bView = false;
		else
			m_bView = true;

	}

	if (m_bView)
		m_pBridge->Progress(m_tInfo);	

}

void	CStore::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CStore::Release(void)
{
	::Safe_Delete(m_pBridge);
}
