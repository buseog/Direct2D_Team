#include "StdAfx.h"
#include "LongAttack.h"

CLongAttack::CLongAttack(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CLongAttack::CLongAttack(UNITDATA*	tUnit) :CUnit(tUnit)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tUnitData = *tUnit;
}

CLongAttack::~CLongAttack(void)
{
	Release();
}

HRESULT CLongAttack::Initialize(void)
{
	m_fSpeed = 65.f;
	m_iOrder = OD_MOVE;
	return S_OK;
}

void CLongAttack::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void CLongAttack::Render(void)
{
	m_pBridge->Render();
}

void CLongAttack::Release(void)
{
	::Safe_Delete(m_pBridge);
}