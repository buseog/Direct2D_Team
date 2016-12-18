#include "StdAfx.h"
#include "BasicTownButton.h"

CBasicTownButton::CBasicTownButton(void)
{
}

CBasicTownButton::~CBasicTownButton(void)
{
}

HRESULT	CBasicTownButton::Initialize(void)
{
	m_wstrObjKey = L"Basic";

	m_tInfo.vSize.x = 148.f;
	m_tInfo.vSize.y = 82.f;
	m_tInfo.vSize.z = 0.f;

	return S_OK;
}

void CBasicTownButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CBasicTownButton::Render(void)
{
	m_pBridge->Render();

}

void CBasicTownButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}