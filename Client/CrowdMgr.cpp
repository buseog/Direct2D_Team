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
	// ���ø���Ʈ�� ������� �������� �۵�
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
	// �Էµ� ������ ���õ� �������� �ٲٰ� ���ø���Ʈ�� �߰���
	pObj->SetSelect(true);
	m_vecSelectUnit.push_back(pObj);

}

// ���õ� ���� ��Ʈ����Ʈ
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
		// �Էµ� ��ġ�� ���긶ũ�� ������
		CObjMgr::GetInstance()->AddObject(OBJ_EFFECT, CObjFactory<CEffect, CStandEffectBridge>::CreateObj(L"MoveMark", vMouse));

		// ����Ʈ�� ��ȸ��
		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			// �� ������ ���鼭 vMouse�������� ���̽�Ÿ�� �۵���Ŵ
			((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(vMouse);
			// ������ ���̽�Ÿ�� �۵���Ŵ
			m_vecSelectUnit[i]->SetOrder(OD_ASTAR);
		}
		clock_t end = clock();

		TCHAR str[256];
		wsprintf(str, TEXT("Creature count : %d, Elapsed Time : %d(ms)\n"), m_vecSelectUnit.size(), end - start);
		OutputDebugString(str);
	}


	if (CKeyMgr::GetInstance()->KeyDown(VK_F1))
	{
		// ���콺�� ȭ�鿡 ������������ ��ũ�Ѱ��� �������
		D3DXVECTOR3 vMouse = ::GetMouse() - m_vecSelectUnit[0]->GetScroll();

		// ĳ���� �ֺ��� �𿩵� ����, ���° �׵θ�����
		float	fAngle = 0.f;
		int		iLine = 1;

		for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
		{
			// ù���� ������ ��� �߽����� �������
			if (i == 0)
			{
				// ����������� ���������� �ٶ󺸴� ������ ����. �����ѵ� �ٶ� ����
				D3DXVECTOR3 vTemp = D3DXVECTOR3(1.f, 0.f, 0.f);
				D3DXVECTOR3	vDir = ::GetMouse() - m_vecSelectUnit[i]->GetInfo()->vPos;
				D3DXVec3Normalize(&vDir, &vDir);

				float fDot = D3DXVec3Dot(&vDir, &vTemp);
				fDot = acosf(fDot);
				
				if ( m_vecSelectUnit[i]->GetInfo()->vPos.y < ::GetMouse().y)
					fDot = 2 * D3DX_PI - fDot;

				// �߽��� �Ǵ� ������ �Է��������� �̵���
				m_vecSelectUnit[0]->SetTargetPoint(D3DXVECTOR3(vMouse.x, vMouse.y, 0));
				m_vecSelectUnit[i]->SetRevolution(fDot);
				m_vecSelectUnit[i]->SetOrder(OD_MOVE);
				continue;
			}
			// ����ó�� 360���� ������ 1���� ���� �޿���̹Ƿ�, �׵θ��� �ø��� ������ �ʱ�ȭ��Ŵ
			if (fAngle == 360)
			{
				fAngle = 0;
				++iLine;
			}
			// ����Ʈ�� ��ȸ�Ҷ����� Ư�� ���� + �׵θ��� ��ġ�� ��������
			float fX = vMouse.x + cosf(D3DXToRadian(fAngle)) * 60 * iLine;
			float fY = vMouse.y - sinf(D3DXToRadian(fAngle)) * 60 * iLine;

			//((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(D3DXVECTOR3(fX, fY, 0.f));
			//m_vecSelectUnit[i]->SetRevolution(D3DXToRadian(fAngle));
			//m_vecSelectUnit[i]->SetOrder(OD_ASTAR);

			// ������ ������ ���ֵ鿡�� ���������� Ÿ������Ʈ�� ��������
			m_vecSelectUnit[i]->SetTargetPoint(D3DXVECTOR3(fX, fY, 0));
			m_vecSelectUnit[i]->SetRevolution(D3DXToRadian(fAngle));
			m_vecSelectUnit[i]->SetOrder(OD_MOVE);

			// �׵θ��� ���������� ���� �������� �Ÿ��� �־������� �׵θ� ���ڿ� �ݺ���ϰ� ������ ������
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
		// ����Ʈ���� ��� ���ֵ��� ���õ������� ���� �ٲٰ�
		m_vecSelectUnit[i]->SetSelect(false);
		CDataSubject::GetInstance()->RemoveData(i, m_vecSelectUnit[i]->GetStat());
		((CUIObserver*)((CPortrait*)m_vecPortrait[i])->GetObserver())->SetIndex(-1);
	}
	CDataSubject::GetInstance()->Release();
	// ����Ʈ�� Ŭ������
	m_vecSelectUnit.clear();

	for (size_t i = 0; i < m_vecPortrait.size(); ++i)
	{
		// ����Ʈ���� ��� ���ֵ��� ���õ������� ���� �ٲٰ�
		m_vecPortrait[i]->GetBridge()->SetKey(L"");
	}
}