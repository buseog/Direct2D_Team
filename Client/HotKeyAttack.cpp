#include "StdAfx.h"
#include "HotKeyAttack.h"

CHotKeyAttack::CHotKeyAttack(void)
{
}

CHotKeyAttack::~CHotKeyAttack(void)
{
}

HRESULT	CHotKeyAttack::Initialize(void)
{
	m_wstrObjKey = L"HotKeyAttack";
	return S_OK;
}

void CHotKeyAttack::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CHotKeyAttack::Render(void)
{
	m_pBridge->Render();

}

void CHotKeyAttack::Release(void)
{
	::Safe_Delete(m_pBridge);
}