#include "StdAfx.h"
#include "UnitBridge.h"
#include "Obj.h"
#include "AStar.h"
#include "TimeMgr.h"
#include "ObjMgr.h"

CUnitBridge::CUnitBridge(void)
{
}

CUnitBridge::~CUnitBridge(void)
{
	Release();
}


HRESULT CUnitBridge::Initialize(void)
{
	m_wstrStateKey = L"Walk_1";

	return S_OK;
}

void CUnitBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);
	CBridge::Frame();
	

	switch (m_pObj->GetOrder())
	{
	case OD_STAND:
		Stop(rInfo);
		break;

	case OD_MOVE:
		Move(rInfo);
		break;

	case OD_ASTAR:
		AStarMove(rInfo);
		break;

	case OD_PATROL:
		Patrol(rInfo);
		break;

	case OD_ATTACK:
		Attack(rInfo);
		break;

	case OD_SKILL:
		Skill(rInfo);
		break;
	}

	KeyInput(rInfo);

}

void CUnitBridge::Render(void)
{
	if (m_pObj->GetSelect())
	{
		const TEXINFO*		pSelTexture = CTextureMgr::GetInstance()->GetTexture(L"SelectEffect");

		if(pSelTexture == NULL)
			return;

		float fX = pSelTexture->tImgInfo.Width / 2.f;
		float fY = pSelTexture->tImgInfo.Height / 2.f + 30;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
		CDevice::GetInstance()->GetSprite()->Draw(pSelTexture->pTexture, 
			NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	}

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
		m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f + 30.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUnitBridge::Release(void)
{
	
}

void	CUnitBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matScale, matTrans;

	// ĳ���� �¿� �����ϸ� ���
	if (rInfo.vDir.x < 0)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	}
	else
	{
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	}

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matScale * matTrans;
}

void	CUnitBridge::KeyInput(INFO& rInfo)
{
	
}

void	CUnitBridge::Move(INFO& rInfo)
{
	// ���� ������ �޾������� �� �����Լ��� ���
	// ��ǥ�������� ���⺤�͸� ���ؼ��Ÿ��� 10�̻��϶��� ������.
	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Walk_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Walk_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Walk_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Walk_3");

	else
		SetFrame(L"Walk_4");

	if(fDistance > 10.f)
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	else
	{
		rInfo.vDir.x = cosf(m_pObj->GetRevolution());
		rInfo.vDir.y = -sinf(m_pObj->GetRevolution());
		m_pObj->SetOrder(OD_STAND);
		SetFrame(L"Stand_1");
	}

}

void	CUnitBridge::SetAstar(D3DXVECTOR3 vMouse)
{
	// ���̽�Ÿ �۵�����
	m_vecBestList.clear();
	CAStar::GetInstance()->StartPos(m_pObj->GetInfo()->vPos, vMouse, &m_vecBestList);
}

void	CUnitBridge::AStarMove(INFO& rInfo)
{
	// ���̽�Ÿ ������ �޾������� �� ���긦 �����
	if(m_vecBestList.empty())
		return;

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();
	
	if(pVecTile == NULL)
		return;

	int		iMoveIndex = m_vecBestList.front();

	rInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - rInfo.vPos;
	float	fDistance = D3DXVec3Length(&rInfo.vDir);

	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Walk_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Walk_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Walk_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Walk_3");

	else
		SetFrame(L"Walk_4");

	rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();

	if(fDistance < m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime())
	{
		m_vecBestList.pop_front();
	}
	if (m_vecBestList.empty())
	{
		m_pObj->SetOrder(OD_STAND);
		SetFrame(L"Stand_1");
	}
}

void	CUnitBridge::Attack(INFO& rInfo)
{
	// ���� ������ �޾������� �� �����Լ��� ���
	// ��ǥ�������� ���⺤�͸� ���ؼ��Ÿ��� 10�̻��϶��� ������.
	list<CObj*>* pMonList = CObjMgr::GetInstance()->GetObjList(SC_BATTLEFIELD, OBJ_MONSTER);
	RECT rc;


	for (list<CObj*>::iterator iter = pMonList->begin(); iter != pMonList->end(); ++iter)
	{
		if (IntersectRect(&rc, &(*iter)->GetRect(), &m_pObj->GetRect()))
		{
			rInfo.vDir = (*iter)->GetInfo()->vPos - rInfo.vPos;

			float	fDistance = D3DXVec3Length(&rInfo.vDir);
			D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

			// ĳ���� y������ ���� ���� ��ȯ
			if (rInfo.vDir.y >= 0.75f)
				SetFrame(L"Attack_5");

			else if (rInfo.vDir.y >= 0.25f)
				SetFrame(L"Attack_1");

			else if (rInfo.vDir.y >= -0.25f)
				SetFrame(L"Attack_2");

			else if (rInfo.vDir.y >= -0.75f)
				SetFrame(L"Attack_3");

			else
				SetFrame(L"Attack_4");


			return;
		}
	}

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Walk_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Walk_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Walk_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Walk_3");

	else
		SetFrame(L"Walk_4");

	if(fDistance > 10.f)
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	
	
	
}

void	CUnitBridge::Stop(INFO& rInfo)
{
	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Stand_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Stand_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Stand_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Stand_3");

	else
		SetFrame(L"Stand_4");
}

void	CUnitBridge::Patrol(INFO& rInfo)
{
	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Walk_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Walk_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Walk_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Walk_3");

	else
		SetFrame(L"Walk_4");

	if(fDistance > m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime())
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	else
	{
		D3DXVECTOR3 vSwap = m_pObj->GetTargetPoint();
		m_pObj->SetTargetPoint(m_pObj->GetOriginPos());
		m_pObj->SetOriginPos(vSwap);
	}
}

void	CUnitBridge::Skill(INFO&	rInfo)
{
	if (rInfo.vDir.y >= 0.75f)
		SetFrame(L"Skill_5");

	else if (rInfo.vDir.y >= 0.25f)
		SetFrame(L"Skill_1");

	else if (rInfo.vDir.y >= -0.25f)
		SetFrame(L"Skill_2");

	else if (rInfo.vDir.y >= -0.75f)
		SetFrame(L"Skill_3");

	else
		SetFrame(L"Skill_4");
}