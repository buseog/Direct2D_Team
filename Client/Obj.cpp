#include "StdAfx.h"
#include "Obj.h"

D3DXVECTOR3	CObj::m_vScroll;

CObj::CObj(void)
: m_wstrObjKey(L"")
, m_pBridge(NULL)
, m_bDestroy(false)
, m_bSelect(false)
, m_fRotation(0.f)
, m_fRevolution(0.f)
, m_iOrder(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_vTargetPoint, sizeof(D3DXVECTOR3));
	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
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

void CObj::SetDestroy(bool	_YN)
{
	m_bDestroy = _YN;
}

void	CObj::SetSelect(bool YN)
{
	m_bSelect = YN;
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

const	bool	CObj::GetDestroy(void)
{
	return m_bDestroy;
}

const D3DXVECTOR3	CObj::GetScroll(void)
{
	return m_vScroll;
}

const bool			CObj::GetSelect(void)
{
	return m_bSelect;
}

const D3DXVECTOR3	CObj::GetTargetPoint(void)
{
	return m_vTargetPoint;
}

void	CObj::SetTargetPoint(D3DXVECTOR3 pTargetPoint)
{
	m_vTargetPoint = pTargetPoint;
}

void	CObj::SetRevolution(float fAngle)
{
	m_fRevolution = fAngle;
}

const float CObj::GetRevolution(void)
{
	return m_fRevolution;
}

void	CObj::SetOrder(ORDERID eOrder)
{
	m_iOrder = eOrder;
}

const int CObj::GetOrder(void)
{
	return m_iOrder;
}

const RECT CObj::GetRect(void)
{
	RECT rc = {
		long(m_tInfo.vPos.x - m_tInfo.vSize.x),
		long(m_tInfo.vPos.y - m_tInfo.vSize.y),
		long(m_tInfo.vPos.x + m_tInfo.vSize.x),
		long(m_tInfo.vPos.y + m_tInfo.vSize.y)
	};

	return rc;
}