#include "StdAfx.h"
#include "PlayerBridge.h"
#include "Obj.h"
#include "AStar.h"
#include "TimeMgr.h"
#include "EnemyBridge.h"
#include "EnemyUnit.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"

CPlayerBridge::CPlayerBridge(void)
{
	Release();
}
	
CPlayerBridge::~CPlayerBridge(void)
{
}

HRESULT CPlayerBridge::Initialize(void)
{
	return S_OK;
}

void CPlayerBridge::Progress(INFO& rInfo)
{
	WorldMatrix(rInfo);

	Frame();

	switch (m_pObj->GetOrder())
	{
	case OD_STAND:
		break;

	case OD_MOVE:
		Move(rInfo);
		break;

	case OD_ASTAR:
		AStarMove(rInfo);
		break;
	}

	KeyInput(rInfo);
}

void CPlayerBridge::Render(void)
{
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

void CPlayerBridge::Release(void)
{
	
}

void	CPlayerBridge::WorldMatrix(INFO& rInfo)
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

void	CPlayerBridge::SetAstar(D3DXVECTOR3 vMouse)
{
	m_vecBestList.clear();
	CAStar::GetInstance()->StartPos(m_pObj->GetInfo()->vPos, vMouse, &m_vecBestList);
}

void	CPlayerBridge::KeyInput(INFO& rInfo)
{
	if (CKeyMgr::GetInstance()->KeyDown(VK_RBUTTON))
	{
		D3DXVECTOR3 vMouse = ::GetMouse();
		vMouse -= m_pObj->GetScroll();
		SetAstar(vMouse);
		m_pObj->SetOrder(OD_ASTAR);

	}
}

void	CPlayerBridge::Move(INFO& rInfo)
{
	// ���� ������ �޾������� �� �����Լ��� ���
	// ��ǥ�������� ���⺤�͸� ���ؼ��Ÿ��� 10�̻��϶��� ������.
	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// ĳ���� y������ ���� ���� ��ȯ
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Walk_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Walk_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Walk_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Walk_3";

	else
		m_wstrStateKey = L"Walk_4";

	if(fDistance > 10)
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	else
	{
		m_pObj->SetOrder(OD_STAND);
	}
}


void	CPlayerBridge::AStarMove(INFO& rInfo)
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
		m_wstrStateKey = L"Walk_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Walk_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Walk_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Walk_3";

	else
		m_wstrStateKey = L"Walk_4";

	

	if(fDistance > 10)
	{
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	}
	else
		m_vecBestList.pop_front();

	if (m_vecBestList.empty())
		m_pObj->SetOrder(OD_STAND);
}