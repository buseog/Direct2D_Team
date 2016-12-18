#include "StdAfx.h"
#include "CrowdMgr.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AStar.h"
#include "DataSubject.h"
#include "UiObserver.h"

#include "ObjFactory.h"
#include "UiFactory.h"

#include "Obj.h"
#include "UnitBridge.h"
#include "Effect.h"
#include "StandEffectBridge.h"

#include "Portrait.h"
#include "PortraitBridge.h"

#include "SKillMgr.h"

IMPLEMENT_SINGLETON(CCrowdMgr)

CCrowdMgr::CCrowdMgr(void)
:m_iAstarCount(0)
,m_iLimit(0)
,m_bStart(false)
{
	float fCX = 72;
	float fCY = 26;

	int iX = 1;
	int iY = 0;

	for (int i = 0; i < 10; ++i)
	{
		float fX = 215.f + (fCX * iX);
		float fY = 540.f + ((fCY + 15) * iY);

		if (iX == 5)
		{
			iX = 0;
			++iY;
		}

		m_vecPortrait.push_back(CUIFactory<CPortrait, CPortraitBridge>::CreateUI(L"Player", fX, fY));

		++iX;
	}
}

CCrowdMgr::~CCrowdMgr(void)
{
	Release();
}

void CCrowdMgr::Release(void)
{
	m_vecSelectUnit.clear();

	for_each(m_vecPortrait.begin(), m_vecPortrait.end(), DeleteObj());
	m_vecPortrait.clear();
}

int	CCrowdMgr::GetSelectList(void)
{
	return m_vecSelectUnit.size();
}

int	CCrowdMgr::Progress(void)
{
	int iResult = -1;
	// 선택리스트가 비어있지 않을때만 작동
	if (m_vecSelectUnit.empty())
		return -1;

	if (CSceneMgr::GetInstance()->GetMouse() == L"Hand_Stand")
		iResult = KeyInput();

	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		int iKey = (int)i;
		CDataSubject::GetInstance()->Notify();
	}

	return iResult;
}

void	CCrowdMgr::AddSelectList(CObj*	pObj)
{
	// 입력된 유닛을 선택된 유닛으로 바꾸고 선택리스트에 추가함
	pObj->SetSelect(true);
	m_vecSelectUnit.push_back(pObj);

}

// 선택된 유닛 포트라이트
void	CCrowdMgr::RenderPortrait(void)
{
	if (m_vecSelectUnit.empty())
		return;

	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		m_vecPortrait[i]->GetBridge()->SetKey(m_vecSelectUnit[i]->GetObjKey());
		CDataSubject::GetInstance()->AddData((int)i, m_vecSelectUnit[i]->GetStat());
		((CUIObserver*)((CPortrait*)m_vecPortrait[i])->GetObserver())->SetIndex((int)i);
		//((CPortraitBridge*)m_vecPortrait[i]->GetBridge())->SetIndex(i);
	}

	for (size_t i = 0; i < m_vecPortrait.size(); ++i)
	{
		m_vecPortrait[i]->Progress();
		m_vecPortrait[i]->Render();
	}
}

int	CCrowdMgr::KeyInput(void)
{
	POINT pt;
	pt.x = (long)::GetMouse().x;
	pt.y = (long)::GetMouse().y;

	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		if (PtInRect(&m_vecPortrait[i]->GetRect(), pt))
		{
			if (CKeyMgr::GetInstance()->KeyDown(VK_LBUTTON, 1))
			{
				CObj*	pObj = m_vecSelectUnit[i];
				Clear();
				AddSelectList(pObj);

				m_vecPortrait.front()->GetBridge()->SetKey(m_vecSelectUnit.front()->GetObjKey());
				CDataSubject::GetInstance()->AddData(0, m_vecSelectUnit.front()->GetStat());
				((CUIObserver*)((CPortrait*)m_vecPortrait.front())->GetObserver())->SetIndex(0);

				return 1;
			}
		}
	}


	if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		clock_t start = clock();
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit.front()->GetScroll();
		// 입력된 위치에 무브마크를 생성함
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"MoveMark", vMouse));

		// 리스트를 순회함
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			// 각 유닛을 돌면서 vMouse지점으로 에이스타를 작동시킴
			((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(vMouse);
			// 오더를 에이스타로 작동시킴
			m_vecSelectUnit[i]->SetOrder(OD_ASTAR);
		}
		clock_t end = clock();

		TCHAR str[256];
		wsprintf(str, TEXT("Creature count : %d, Elapsed Time : %d(ms)\n"), m_vecSelectUnit.size(), end - start);
		OutputDebugString(str);
	}


	if (CKeyMgr::GetInstance()->KeyDown(VK_F1))
	{
		// 마우스는 화면에 갇혀있음으로 스크롤값을 계산해줌
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit[0]->GetScroll();

		// 캐릭터 주변에 모여들 각도, 몇번째 테두리인지
		float	fAngle = 0.f;
		int		iLine = 1;

		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			// 첫번쨰 유닛을 경우 중심으로 만들어줌
			if (i == 0)
			{
				// 출발지점에서 도착지점을 바라보는 각도를 구함. 도착한뒤 바라볼 방향
				D3DXVECTOR3 vTemp = D3DXVECTOR3(1.f, 0.f, 0.f);
				D3DXVECTOR3	vDir = ::GetMouse() - m_vecSelectUnit[i]->GetInfo()->vPos;
				D3DXVec3Normalize(&vDir, &vDir);

				float fDot = D3DXVec3Dot(&vDir, &vTemp);
				fDot = acosf(fDot);
				
				if ( m_vecSelectUnit[i]->GetInfo()->vPos.y < ::GetMouse().y)
					fDot = 2 * D3DX_PI - fDot;

				// 중심이 되는 유닛은 입력지점으로 이동함
				m_vecSelectUnit[0]->SetTargetPoint(D3DXVECTOR3(vMouse.x, vMouse.y, 0));
				m_vecSelectUnit[i]->SetRevolution(fDot);
				m_vecSelectUnit[i]->SetOrder(OD_MOVE);
				continue;
			}
			// 예외처리 360도가 넘으면 1줄을 가득 메운것이므로, 테두리를 늘리고 각도를 초기화시킴
			if (fAngle == 360)
			{
				fAngle = 0;
				++iLine;
			}
			// 리스트를 순회할때마다 특정 각도 + 테두리의 위치를 지정해줌
			float fX = vMouse.x + cosf(D3DXToRadian(fAngle)) * 60 * iLine;
			float fY = vMouse.y - sinf(D3DXToRadian(fAngle)) * 60 * iLine;

			//((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(D3DXVECTOR3(fX, fY, 0.f));
			//m_vecSelectUnit[i]->SetRevolution(D3DXToRadian(fAngle));
			//m_vecSelectUnit[i]->SetOrder(OD_ASTAR);

			// 구해진 값으로 유닛들에게 순차적으로 타겟포인트를 지정해줌
			m_vecSelectUnit[i]->SetTargetPoint(D3DXVECTOR3(fX, fY, 0));
			m_vecSelectUnit[i]->SetRevolution(D3DXToRadian(fAngle));
			m_vecSelectUnit[i]->SetOrder(OD_MOVE);

			// 테두리가 벌어질수록 같은 각도여도 거리가 멀어짐으로 테두리 숫자에 반비례하게 각도를 설정함
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

	if (CKeyMgr::GetInstance()->KeyDown('S'))
	{
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			m_vecSelectUnit[i]->SetOrder(OD_STAND);
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown('P'))
	{
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit.front()->GetScroll();

		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			m_vecSelectUnit[i]->SetTargetPoint(D3DXVECTOR3(vMouse.x, vMouse.y, 0));
			m_vecSelectUnit[i]->SetOriginPos(m_vecSelectUnit[i]->GetInfo()->vPos);
			m_vecSelectUnit[i]->SetOrder(OD_PATROL);
		}
	}

	if (CKeyMgr::GetInstance()->KeyDown('Q'))
	{
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit.front()->GetScroll();
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			m_vecSelectUnit[i]->SetDamage(3);
			CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CSKillMgr::Skill(m_vecSelectUnit[i]->GetInfo()->vPos, vMouse, m_vecSelectUnit[i]->GetObjKey()));
		}
	}

	return -1;
}

void	CCrowdMgr::Clear(void)
{
	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		// 리스트안의 모든 유닛들을 선택되지않음 으로 바꾸고
		m_vecSelectUnit[i]->SetSelect(false);
		CDataSubject::GetInstance()->RemoveData(i, m_vecSelectUnit[i]->GetStat());
		((CUIObserver*)((CPortrait*)m_vecPortrait[i])->GetObserver())->SetIndex(-1);
	}
	CDataSubject::GetInstance()->Release();
	// 리스트를 클리어함
	m_vecSelectUnit.clear();

	for (size_t i = 0; i < m_vecPortrait.size(); ++i)
	{
		// 리스트안의 모든 유닛들을 선택되지않음 으로 바꾸고
		m_vecPortrait[i]->GetBridge()->SetKey(L"");
	}
}