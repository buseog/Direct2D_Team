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
