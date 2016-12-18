#include "StdAfx.h"
#include "Unit.h"

CUnit::CUnit(void)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}
CUnit::CUnit(UNITDATA*	tUnit)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	m_tUnitData = *tUnit;
}

CUnit::~CUnit(void)
{
}

HRESULT CUnit::Initialize(void)
{
	return S_OK;
}

void CUnit::Progress(void)
{

}

void CUnit::Render(void)
{

}

void CUnit::Release(void)
{
}

void CUnit::WorldMatrix(void)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x , 
		m_tInfo.vPos.y , 
		0.f);

	m_tInfo.matWorld = matTrans;
}
void CUnit::ScaleSync(void)
{
	D3DXMATRIX matScale ,matTrans;
	D3DXMatrixScaling(&matScale,0.7f,0.7f,0.f);
	D3DXMatrixTranslation(&matTrans, 
		m_tInfo.vPos.x , 
		m_tInfo.vPos.y , 
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

}
