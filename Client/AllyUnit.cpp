#include "StdAfx.h"
#include "AllyUnit.h"

CAllyUnit::CAllyUnit(void)
{
}

CAllyUnit::~CAllyUnit(void)
{
	Release();
}

HRESULT CAllyUnit::Initialize(void)
{
	return S_OK;
}

void CAllyUnit::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void CAllyUnit::Render(void)
{
	m_pBridge->Render();
}

void CAllyUnit::Release(void)
{
	::Safe_Delete(m_pBridge);
}