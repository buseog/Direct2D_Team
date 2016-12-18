#include "StdAfx.h"
#include "StoreButton.h"

CStoreButton::CStoreButton(void)
{
}

CStoreButton::~CStoreButton(void)
{
}

HRESULT	CStoreButton::Initialize(void)
{
	m_wstrObjKey = L"StoreButton";


	return S_OK;
}

void CStoreButton::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CStoreButton::Render(void)
{
	m_pBridge->Render();

}

void CStoreButton::Release(void)
{
	::Safe_Delete(m_pBridge);
}
