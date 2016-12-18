#include "StdAfx.h"
#include "TownButton.h"

CTownButton::CTownButton(void)
{
}

CTownButton::~CTownButton(void)
{
}

HRESULT	CTownButton::Initialize(void)
{
	m_wstrObjKey = L"BigTown";

	m_tInfo.vSize.x = 265.f;
	m_tInfo.vSize.y = 205.f;
	m_tInfo.vSize.z = 0.f;

	return S_OK;
}

void CTownButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CTownButton::Render(void)
{
	m_pBridge->Render();

}

void CTownButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}