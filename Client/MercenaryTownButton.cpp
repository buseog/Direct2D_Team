#include "StdAfx.h"
#include "MercenaryTownButton.h"

CMercenaryTownButton::CMercenaryTownButton(void)
{
}

CMercenaryTownButton::~CMercenaryTownButton(void)
{
}

HRESULT	CMercenaryTownButton::Initialize(void)
{
	m_wstrObjKey = L"Mercenary";

	m_tInfo.vSize.x = 144.f;
	m_tInfo.vSize.y = 82.f;
	m_tInfo.vSize.z = 0.f;

	return S_OK;
}

void CMercenaryTownButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CMercenaryTownButton::Render(void)
{
	m_pBridge->Render();

}

void CMercenaryTownButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}