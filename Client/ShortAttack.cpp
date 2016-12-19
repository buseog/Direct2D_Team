#include "StdAfx.h"
#include "ShortAttack.h"

CShortAttack::CShortAttack(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CShortAttack::CShortAttack(UNITDATA*	tUnit) :CUnit(tUnit)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tUnitData = *tUnit;
}
CShortAttack::~CShortAttack(void)
{
	Release();
}

HRESULT	CShortAttack::Initialize(void)
{
	m_fSpeed = 75.f;
	m_tUnitData.fRange=20.f;
	m_iOrder = OD_MOVE;
	return S_OK;
}

void	CShortAttack::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void	CShortAttack::Render(void)
{
	m_pBridge->Render();
}

void	CShortAttack::Release(void)
{
	::Safe_Delete(m_pBridge);
}