#include "StdAfx.h"
#include "HotKeyStop.h"

CHotKeyStop::CHotKeyStop(void)
{
}

CHotKeyStop::~CHotKeyStop(void)
{
}

HRESULT	CHotKeyStop::Initialize(void)
{
	m_wstrObjKey = L"HotKeyStop";

	return S_OK;
}

void CHotKeyStop::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CHotKeyStop::Render(void)
{
	m_pBridge->Render();

}

void CHotKeyStop::Release(void)
{
	::Safe_Delete(m_pBridge);
}
