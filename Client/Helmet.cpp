#include "StdAfx.h"
#include "Helmet.h"

CHelmet::CHelmet(void)
{
}
CHelmet::CHelmet(ITEM*	tItem) :CItem(tItem)
{

}
CHelmet::~CHelmet(void)
{
	Release();
}
HRESULT CHelmet::Initialize(void)
{
	m_wstrObjKey = L"TestHelmet";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.eType = IT_HELMET;
	m_tItem.iOption = 120;
	return S_OK;
}
void CHelmet::Progress(void)
{
	WorldMatrix();
}

void CHelmet::Release(void)
{
}
