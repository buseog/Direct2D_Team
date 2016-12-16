#include "StdAfx.h"
#include "Item.h"

CItem::CItem(void)
: m_pBridge(NULL)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));

}


CItem::~CItem(void)
{
}


const wstring& CItem::GetObjKey(void)
{
	return m_wstrObjKey;
}

CBridge* CItem::GetBridge(void)
{
	return m_pBridge;
}

void CItem::SetPos(const D3DXVECTOR3& vPos)
{
	m_tInfo.vPos = vPos;
}

void CItem::SetPos(float fX, float fY)
{
	m_tInfo.vPos.x = fX;
	m_tInfo.vPos.y = fY;
	m_tInfo.vPos.z = 0.f;
}

RECT CItem::GetRect(void)
{
	RECT rc = {
				(int)m_tInfo.vPos.x - (int)(m_tInfo.vSize.x / 2.f),
				(int)m_tInfo.vPos.y - (int)(m_tInfo.vSize.y / 2.f),
				(int)m_tInfo.vPos.x + (int)(m_tInfo.vSize.x / 2.f),
				(int)m_tInfo.vPos.y + (int)(m_tInfo.vSize.y / 2.f),

			};
	
	return rc;
}

wstring CItem::GetItemKey(void)
{
	
	return m_wstrObjKey;
}
ITEM* CItem::GetItemInfo(void)
{
	return &m_tItem;
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