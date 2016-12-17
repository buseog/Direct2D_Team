#include "StdAfx.h"
#include "EnemyUnit.h"

CEnemyUnit::CEnemyUnit(void)
{
}

CEnemyUnit::~CEnemyUnit(void)
{
	Release();
}

HRESULT CEnemyUnit::Initialize(void)
{
	m_wstrObjKey = L"EnemyUnit";
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

void CEnemyUnit::Move(void)
{

}