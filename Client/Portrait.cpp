#include "StdAfx.h"
#include "Portrait.h"
#include "UiObserver.h"
#include "DataSubject.h"

CPortrait::CPortrait(void)
: m_pObserver(NULL)
{
	ZeroMemory(&m_tData, sizeof(UNITDATA));
}

CPortrait::~CPortrait(void)
{
	Release();
}

HRESULT	CPortrait::Initialize(void)
{
	m_wstrObjKey = L"Portrait";

	m_pObserver = new CUIObserver;

	CDataSubject::GetInstance()->Subscribe(m_pObserver);

	return S_OK;
}

void CPortrait::Progress(void)
{
	m_tData = *((CUIObserver*)m_pObserver)->GetData();
	m_pBridge->Progress(m_tInfo);	

}

void CPortrait::Render(void)
{
	m_pBridge->Render();

}

void CPortrait::Release(void)
{
	::Safe_Delete(m_pBridge);
	::Safe_Delete(m_pObserver);
}

CObserver*	CPortrait::GetObserver(void)
{
	return m_pObserver;
}