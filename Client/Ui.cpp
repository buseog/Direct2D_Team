#include "StdAfx.h"
#include "Ui.h"

CUi::CUi(void)
:m_pBridge(NULL)
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
		m_tInfo.vPos.x - m_tInfo.vSize.x,
		m_tInfo.vPos.y - m_tInfo.vSize.x,
		m_tInfo.vPos.x + m_tInfo.vSize.x,
		m_tInfo.vPos.y + m_tInfo.vSize.x
	};

	return rc;
}