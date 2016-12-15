#include "StdAfx.h"
#include "Status.h"
#include "Bridge.h"
#include "KeyMgr.h"


CStatus::CStatus(void)
: m_bKeyCheck(false)
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

	if(CKeyMgr::GetInstance()->KeyDown('S'))
	{
		if(m_bKeyCheck)
		{
			m_bKeyCheck = false;
		}
		else
			m_bKeyCheck = true;
	}
	
}

void CStatus::Render(void)
{
	if(m_bKeyCheck)
	{
		m_pBridge->Render();
	}
		
}

void	CStatus::Release(void)
{
	::Safe_Delete(m_pBridge);
}
