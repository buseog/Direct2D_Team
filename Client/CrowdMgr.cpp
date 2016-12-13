#include "StdAfx.h"
#include "CrowdMgr.h"
#include "Obj.h"
#include "UnitBridge.h"
#include "AStar.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CCrowdMgr)

CCrowdMgr::CCrowdMgr(void)
:m_iAstarCount(0)
,m_iLimit(0)
,m_bStart(false)
{
}

CCrowdMgr::~CCrowdMgr(void)
{
	Release();
}

void CCrowdMgr::Release(void)
{
	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		m_vecSelectUnit[i]->SetSelect(false);
	}
	m_vecSelectUnit.clear();
}

vector<CObj*>*	CCrowdMgr::GetSelectList(void)
{
	return &m_vecSelectUnit;
}

void	CCrowdMgr::Progress(void)
{
	if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		clock_t start = clock();
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit[i]->GetScroll();
			((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(vMouse);
			m_vecSelectUnit[i]->SetOrder(OD_ASTAR);
		}
		clock_t end = clock();

		TCHAR str[256];
		wsprintf(str, TEXT("Creature count : %d, Elapsed Time : %d(ms)\n"), m_vecSelectUnit.size(), end - start);
		OutputDebugString(str);
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_F1))
	{
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit[0]->GetScroll();
		
		float	fAngle = 0.f;
		int		iLine = 1;

		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			if (i == 0)
			{
				m_vecSelectUnit[0]->SetTargetPoint(D3DXVECTOR3(vMouse.x, vMouse.y, 0));
				m_vecSelectUnit[i]->SetOrder(OD_MOVE);
				continue;
			}
			if (fAngle == 360)
			{
				fAngle = 0;
				++iLine;
			}

			float fX = vMouse.x + cosf(D3DXToRadian(fAngle)) * 50 * iLine;
			float fY = vMouse.y - sinf(D3DXToRadian(fAngle)) * 50 * iLine;
			m_vecSelectUnit[i]->SetTargetPoint(D3DXVECTOR3(fX, fY, 0));
			m_vecSelectUnit[i]->SetRevolution(D3DXToRadian(fAngle));
			m_vecSelectUnit[i]->SetOrder(OD_MOVE);
			
			fAngle += 60.f / iLine;
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown(VK_F2))
	{
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit[0]->GetScroll();
		
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			if (i % 2 == 0)
			{
				
			}
		}
	}

	
}