#include "StdAfx.h"
#include "BattlePannel.h"

CBattlePannel::CBattlePannel(void)
{
}

CBattlePannel::~CBattlePannel(void)
{
	Release();
}

HRESULT	CBattlePannel::Initialize(void)
{
	m_wstrObjKey = L"BattlePannel";

	return S_OK;
}

void CBattlePannel::Progress(void)
{
	
	m_pBridge->Progress(m_tInfo);	

}

void CBattlePannel::Render(void)
{
	m_pBridge->Render();

}

void CBattlePannel::Release(void)
{
	::Safe_Delete(m_pBridge);
}
