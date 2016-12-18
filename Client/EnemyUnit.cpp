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
	//m_wstrObjKey = L"EnemyUnit";
	m_fSpeed = 30.f;
	m_vTargetPoint = D3DXVECTOR3(500.f, 200.f, 0.f);
	m_vOriginPos   = D3DXVECTOR3(400.f, 300.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(130.f,140.f,0.f);

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

