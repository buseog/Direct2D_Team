#include "StdAfx.h"
#include "Back.h"
#include "TimeMgr.h"
#include "ObjFactory.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Player.h"
#include "EnemyUnit.h"
#include "UnitBridge.h"
#include "BackBridge.h"
#include "EnemyBridge.h"
#include "AllyUnit.h"

CBack::CBack(void)
{
}

CBack::~CBack(void)
{
	Release();
}

HRESULT CBack::Initialize(void)
{
	m_fSpeed = 500.f;

	MouseLock();

	return S_OK;
}

void CBack::Progress(void)
{
	m_pBridge->Progress(m_tInfo);
	MoveScroll();

	float MaxX = -(((CBackBridge*)m_pBridge)->GetSize()->x - (float)WINCX - 40);
	float MaxY = -(((CBackBridge*)m_pBridge)->GetSize()->y - (float)WINCY - 20);

	if (m_vScroll.x > 0.f)
		m_vScroll.x = 0.f;

	if (m_vScroll.x < MaxX)
		m_vScroll.x = MaxX;

	if (m_vScroll.y > 0.f)
		m_vScroll.y = 0.f;

	if (m_vScroll.y < MaxY)
		m_vScroll.y = MaxY;



	if (CKeyMgr::GetInstance()->KeyDown('1'))
	{
		D3DXVECTOR3 vPos = ::GetMouse() - m_vScroll;
		CObjMgr::GetInstance()->AddObject(OBJ_UNIT, CObjFactory<CAllyUnit, CUnitBridge>::CreateObj(L"YiSunshin", L"Walk_1", D3DXVECTOR3(vPos.x, vPos.y, 0.f)));
	}

	if (CKeyMgr::GetInstance()->KeyDown('2'))
	{
		D3DXVECTOR3 vPos = ::GetMouse() - m_vScroll;
		CObjMgr::GetInstance()->AddObject(OBJ_MONSTER, CObjFactory<CPlayer, CUnitBridge>::CreateObj(L"Walk_1", vPos.x, vPos.y));
	}



	
}

void CBack::Render(void)
{
	m_pBridge->Render();
}

void CBack::Release(void)
{
	::Safe_Delete(m_pBridge);
}

const vector<TILE2*>* CBack::GetTile(void)
{
	return ((CBackBridge*)m_pBridge)->GetTile();
}


void	CBack::MoveScroll(void)
{
	D3DXVECTOR3		vMousePos = ::GetMouse();

	if(vMousePos.x < 20)
		m_vScroll.x += m_fSpeed * CTimeMgr::GetInstance()->GetTime();


	if(WINCX - 20 < vMousePos.x)
		m_vScroll.x -= m_fSpeed * CTimeMgr::GetInstance()->GetTime();


	if(20 > vMousePos.y)
		m_vScroll.y += m_fSpeed * CTimeMgr::GetInstance()->GetTime();

	if(WINCY - 20 < vMousePos.y)
		m_vScroll.y -= m_fSpeed * CTimeMgr::GetInstance()->GetTime();
}

void	CBack::MouseLock(void)
{
	RECT rc;
	GetWindowRect(g_hWnd, &rc);
	rc.left += 20;
	rc.top += 40;
	rc.right -= 20;
	rc.bottom -= 20;
	ClipCursor(&rc);
}
