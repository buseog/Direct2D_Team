#include "StdAfx.h"
#include "Boots.h"

CBoots::CBoots(void)
{
}
CBoots::CBoots(ITEM*	tItem) :CItem(tItem)
{

}
CBoots::~CBoots(void)
{
	Release();
}
HRESULT CBoots::Initialize(void)
{
	m_wstrObjKey = L"TestBoots";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.eType = IT_BOOTS;
	m_tItem.iOption = 40;
	return S_OK;
}
void CBoots::Progress(void)
{
	WorldMatrix();
}

void CBoots::Release(void)
{
}
