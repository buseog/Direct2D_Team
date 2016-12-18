#include "StdAfx.h"
#include "Glove.h"

CGlove::CGlove(void)
{
}
CGlove::CGlove(ITEM*	tItem) :CItem(tItem)
{

}

CGlove::~CGlove(void)
{
	Release();
}
HRESULT CGlove::Initialize(void)
{
	m_wstrObjKey = L"TestGlove";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.eType = IT_GLOVE;
	m_tItem.iOption = 20;
	return S_OK;
}
void CGlove::Progress(void)
{
	WorldMatrix();
}

void CGlove::Release(void)
{
}
