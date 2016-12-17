#include "StdAfx.h"
#include "MyButton.h"

CMyButton::CMyButton(void)
{
}

CMyButton::~CMyButton(void)
{
	Release();
}

HRESULT	CMyButton::Initialize(void)
{
	m_wstrObjKey = L"Button";
	m_tInfo.vSize.x = 16.f;
	m_tInfo.vSize.y = 15.f;
	m_tInfo.vSize.z = 0.f;


	return S_OK;
}

void CMyButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CMyButton::Render(void)
{
	m_pBridge->Render();

}

void CMyButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}
