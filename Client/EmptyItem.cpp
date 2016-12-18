#include "StdAfx.h"
#include "EmptyItem.h"

CEmptyItem::CEmptyItem(void)
{
}

CEmptyItem::~CEmptyItem(void)
{
	Release();
}


HRESULT CEmptyItem::Initialize(void)
{
	m_wstrObjKey = L"Empty";
	m_tInfo.vSize = D3DXVECTOR3(60.f,60.f,0.f);
	m_tItem.eType = IT_EMPTY;
	m_tItem.iOption = 0;
	return S_OK;
}
void CEmptyItem::Progress(void)
{
	
	
}
void CEmptyItem::Render(void)
{

}
void CEmptyItem::Release(void)
{

}
