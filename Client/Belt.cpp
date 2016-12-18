#include "StdAfx.h"
#include "Belt.h"

CBelt::CBelt(void)
{
}
CBelt::CBelt(ITEM*	tItem) :CItem(tItem)
{

}
CBelt::~CBelt(void)
{
	Release();
}
HRESULT CBelt::Initialize(void)
{
	m_wstrObjKey = L"TestBelt";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.eType = IT_BELT;
	return S_OK;
}
void CBelt::Progress(void)
{
	WorldMatrix();
}

void CBelt::Release(void)
{
}
