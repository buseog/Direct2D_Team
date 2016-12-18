#include "StdAfx.h"
#include "EmptyUnit.h"

CEmptyUnit::CEmptyUnit(void)
{
}

CEmptyUnit::~CEmptyUnit(void)
{
	Release();
}


HRESULT CEmptyUnit::Initialize(void)
{
	m_wstrObjKey = L"Empty";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tUnitData.tDetail.UnitType= UNIT_EMPTY;
	return S_OK;
}
void CEmptyUnit::Progress(void)
{
	
	
}
void CEmptyUnit::Render(void)
{

}
void CEmptyUnit::Release(void)
{

}
