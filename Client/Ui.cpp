#include "StdAfx.h"
#include "Ui.h"
#include "UiBridge.h"

CUi::CUi(void)
:m_pBridge(NULL)
,m_bView(false)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
}

CUi::~CUi(void)
{

}

const INFO* CUi::GetInfo(void) const
{
	return &m_tInfo;
}

		
void CUi::SetPos(const D3DXVECTOR3& vPos)
{
	m_tInfo.vPos = vPos;
}

void CUi::SetPos(float fX, float fY)
{
	m_tInfo.vPos.x = fX;
	m_tInfo.vPos.y = fY;
	m_tInfo.vPos.z = 0.f;
	
}
const wstring& CUi::GetObjKey(void)
{
	return m_wstrObjKey;
}

void CUi::SetBridge(CBridge* pBridge)
{

	m_pBridge = pBridge;
}

const RECT CUi::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.vPos.x - m_tInfo.vSize.x),
		long(m_tInfo.vPos.y - m_tInfo.vSize.y),
		long(m_tInfo.vPos.x + m_tInfo.vSize.x),
		long(m_tInfo.vPos.y + m_tInfo.vSize.y)
	};

	return rc;
}

int CUi::Picking(void)
{
	return m_pBridge->Picking();
}

CBridge* CUi::GetBridge(void)
{
	return m_pBridge;
}

int CUi::GetIndexKey(void)
{
	return m_iIndexKey;
}

void CUi::SetIndexKey(int _iIndex)
{
	m_iIndexKey = _iIndex;
}

void	CUi::SetSize(D3DXVECTOR3 vSize)
{
	m_tInfo.vSize = vSize;
}
