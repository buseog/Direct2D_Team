#include "StdAfx.h"
#include "Store.h"
#include "Bridge.h"
#include "StoreBridge.h"
//#include "Item.h"
//#include "Armor.h"

CStore::CStore(void)
{
}

CStore::~CStore(void)
{
	Release();
}


HRESULT	CStore::Initialize(void)
{
	m_wstrObjKey = L"Store";	
	//m_pBridge->Initialize();
	
	return S_OK;
	
}

void	CStore::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	
	


}

void	CStore::Render(void)
{
	if(GetKeyState('L') && 0x0001)
	{
		((CStoreBridge*)m_pBridge)->SetState();
		m_pBridge->Render();
	}

}

void	CStore::Release(void)
{
	::Safe_Delete(m_pBridge);

}


void	CStore::Picking(void)
{

}
