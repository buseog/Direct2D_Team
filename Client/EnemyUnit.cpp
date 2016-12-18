#include "StdAfx.h"
#include "EnemyUnit.h"

CEnemyUnit::CEnemyUnit(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}
CEnemyUnit::CEnemyUnit(UNITDATA*	tUnit) :CUnit(tUnit)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tUnitData = *tUnit;
}

CEnemyUnit::~CEnemyUnit(void)
{
	Release();
}

HRESULT CEnemyUnit::Initialize(void)
{
	return S_OK;
}

void CEnemyUnit::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
}

void CEnemyUnit::Render(void)
{
	m_pBridge->Render();
}

void CEnemyUnit::Release(void)
{
	::Safe_Delete(m_pBridge);
}