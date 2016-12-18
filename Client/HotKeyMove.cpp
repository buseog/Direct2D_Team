#include "StdAfx.h"
#include "HotKeyMove.h"

CHotKeyMove::CHotKeyMove(void)
{
}

CHotKeyMove::~CHotKeyMove(void)
{
}

HRESULT	CHotKeyMove::Initialize(void)
{
	m_wstrObjKey = L"HotKeyMove";

	return S_OK;
}

void CHotKeyMove::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CHotKeyMove::Render(void)
{
	m_pBridge->Render();

}

void CHotKeyMove::Release(void)
{
	::Safe_Delete(m_pBridge);
}