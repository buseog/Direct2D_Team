#include "StdAfx.h"
#include "Obj.h"

D3DXVECTOR3	CObj::m_vScroll;

CObj::CObj(void)
: m_wstrObjKey(L"")
, m_pBridge(NULL)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}

CObj::~CObj(void)
{
}
void CObj::SetPos(const D3DXVECTOR3& vPos)
{
	m_tInfo.vPos = vPos;
}

void CObj::SetPos(float fX, float fY)
{
	m_tInfo.vPos.x = fX;
	m_tInfo.vPos.y = fY;
	m_tInfo.vPos.z = 0.f;
}

void CObj::SetBridge(CBridge* pBridge)
{
	m_pBridge = pBridge;
}

CBridge* CObj::GetBridge(void)
{
	return m_pBridge;
}

const INFO* CObj::GetInfo(void) const
{
	return &m_tInfo;
}

const wstring& CObj::GetObjKey(void)
{
	return m_wstrObjKey;
}
