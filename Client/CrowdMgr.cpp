#include "StdAfx.h"
#include "CrowdMgr.h"

#include "KeyMgr.h"
#include "ObjMgr.h"
#include "AStar.h"

#include "ObjFactory.h"

#include "Obj.h"
#include "UnitBridge.h"

#include "Effect.h"
#include "StandEffectBridge.h"

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
		// ����Ʈ���� ��� ���ֵ��� ���õ������� ���� �ٲٰ�
		m_vecSelectUnit[i]->SetSelect(false);
	}
	// ����Ʈ�� Ŭ������
	m_vecSelectUnit.clear();
}

vector<CObj*>*	CCrowdMgr::GetSelectList(void)
{
	return &m_vecSelectUnit;
}

void	CCrowdMgr::Progress(void)
{
	// ���ø���Ʈ�� ������� �������� �۵�
	if (m_vecSelectUnit.empty())
		return;

	KeyInput();

	
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

	D3DXMATRIX matTrans;
	int iX = 0;
	int iY = 0;

	for (size_t i = 0; i < m_vecSelectUnit.size(); ++i)
	{
		const TEXINFO*	pTexture = CTextureMgr::GetInstance()->GetTexture(L"Portrait", m_vecSelectUnit[i]->GetObjKey(), 0);

		if (pTexture == NULL)
			return;

		float fX = pTexture->tImgInfo.Width;
		float fY = pTexture->tImgInfo.Height;

		if (iX >= 5)
		{
			iX = 0;
			++iY;
		}

		
		D3DXMatrixTranslation(&matTrans, 260.f + (fX * iX), 530.f + (fY * iY), 0.f);


		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);
		CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX / 2.f, fY / 2.f, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

		++iX;
	}
}

void	CCrowdMgr::KeyInput(void)
{
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
			float fX = vMouse.x + cosf(D3DXToRadian(fAngle)) * 80 * iLine;
			float fY = vMouse.y - sinf(D3DXToRadian(fAngle)) * 80 * iLine;

			/*((CUnitBridge*)m_vecSelectUnit[i]->GetBridge())->SetAstar(D3DXVECTOR3(fX, fY, 0.f));
			m_vecSelectUnit[i]->SetOrder(OD_ASTAR);*/

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
}