#include "StdAfx.h"
#include "Inventory.h"
//#include "Item.h"
#include "KeyMgr.h"

CInventory::CInventory(void)
{
}

CInventory::~CInventory(void)
{
	Release();
}


HRESULT	CInventory::Initialize(void)
{
	m_wstrObjKey = L"Inventory";	
		
	return S_OK;
}

void	CInventory::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown('I'))
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

void	CInventory::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CInventory::Release(void)
{
	::Safe_Delete(m_pBridge);
}
