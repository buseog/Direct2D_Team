#include "StdAfx.h"
#include "MainUi.h"
#include "Bridge.h"

CMainUi::CMainUi(void)
{
}

CMainUi::~CMainUi(void)
{
	Release();
}

HRESULT	CMainUi::Initialize(void)
{
	m_wstrObjKey = L"MainUI";
	
	
	
	return S_OK;
}

void		CMainUi::Progress(void)
{
	

	m_pBridge->Progress(m_tInfo);

}

void	CMainUi::Render(void)
{
	m_pBridge->Render();
	
}

void	CMainUi::Release(void)
{
	::Safe_Delete(m_pBridge);
}

