#include "StdAfx.h"
#include "MercenaryDisplay.h"
//#include "Item.h"
#include "KeyMgr.h"

CMercenaryDisplay::CMercenaryDisplay(void)
{
	m_bView=true;
}

CMercenaryDisplay::~CMercenaryDisplay(void)
{
	Release();
}


HRESULT	CMercenaryDisplay::Initialize(void)
{
//	m_wstrObjKey = L"Inventory";	
		
	return S_OK;
}

void	CMercenaryDisplay::Progress(void)
{
	if (m_bView)
		m_pBridge->Progress(m_tInfo);	

}

void	CMercenaryDisplay::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CMercenaryDisplay::Release(void)
{
	::Safe_Delete(m_pBridge);
}
