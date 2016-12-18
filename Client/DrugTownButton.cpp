#include "StdAfx.h"
#include "DrugTownButton.h"

CDrugTownButton::CDrugTownButton(void)
{
}

CDrugTownButton::~CDrugTownButton(void)
{
}

HRESULT	CDrugTownButton::Initialize(void)
{
	m_wstrObjKey = L"Drug";

	m_tInfo.vSize.x = 230.f;
	m_tInfo.vSize.y = 140.f;
	m_tInfo.vSize.z = 0.f;

	return S_OK;
}

void CDrugTownButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CDrugTownButton::Render(void)
{
	m_pBridge->Render();

}

void CDrugTownButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}