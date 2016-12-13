#include "StdAfx.h"
#include "Status.h"
#include "Bridge.h"
//#include "Item.h"
//#include "Weapon.h"

CStatus::CStatus(void)
{
}

CStatus::~CStatus(void)
{
	Release();
}


HRESULT	CStatus::Initialize(void)
{
	m_wstrObjKey = L"Status";	
		
	return S_OK;
}

void	CStatus::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	
	


}

void	CStatus::Render(void)
{

	m_pBridge->Render();


}

void	CStatus::Release(void)
{
	::Safe_Delete(m_pBridge);
}

void	CStatus::AddItem(void)
{

}

void	CStatus::Picking(void)
{

}
