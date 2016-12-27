#include "StdAfx.h"
#include "BasicStore.h"
#include "KeyMgr.h"

CBasicStore::CBasicStore(void)
{
}

CBasicStore::~CBasicStore(void)
{
}

HRESULT	CBasicStore::Initialize(void)
{
	m_wstrObjKey = L"BASIC";	

	return S_OK;
}

void	CBasicStore::Progress(void)
{
	if(CKeyMgr::GetInstance()->KeyDown('B'))
	{

		if (m_bView == true)
			m_bView = false;
		else
			m_bView = true;

	}

	if (m_bView)
		m_pBridge->Progress(m_tInfo);	

}

void	CBasicStore::Render(void)
{
	if (m_bView)
		m_pBridge->Render();
}

void	CBasicStore::Release(void)
{
	::Safe_Delete(m_pBridge);
}
