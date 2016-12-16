#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
{
}

CItem::~CItem(void)
{
}
wstring CItem::GetItemKey(void)
{
	
	return m_wstrObjKey;
}
ITEM* CItem::GetItemInfo(void)
{
	return &m_tItem;
}
void CItem::SetPos(D3DXVECTOR3 _vPos)
{
	m_tInfo.vPos=_vPos;
}
void CItem::SetItemProperty(wstring _Name, ITEMID _eType,int _iOption,int _iPrice, int _iWeight)
{
	m_tItem.wstrName = _Name;
	m_tItem.eType = _eType;
	m_tItem.iOption = _iOption;
	m_tItem.iPrice = _iPrice;
	m_tItem.iWeight = _iWeight;
}

INFO*	CItem::GetInfo(void)
{
	return &m_tInfo;
}