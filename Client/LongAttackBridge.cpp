#include "StdAfx.h"
#include "LongAttackBridge.h"
#include "Astar.h"
#include "ObjMgr.h"
#include "AllyUnit.h"
#include "Player.h"

CLongAttackBridge::CLongAttackBridge(void)
{
}


CLongAttackBridge::~CLongAttackBridge(void)
{
	Release();
}

HRESULT CLongAttackBridge::Initialize(void)
{
	m_wstrStateKey = L"Walk_1";
	
	return S_OK;
}

void CLongAttackBridge::Progress(INFO& rInfo)
{	
	WorldMatrix(rInfo);
	Frame();
	ArtificiaIintelligence(rInfo);
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

		case OD_ATTACK:
			Attack(rInfo);
			break;

		case OD_DIE:
			m_pObj->SetDestroy(true);

		case OD_BACK:
			Back(rInfo);

			break;
	}
}

void	CLongAttackBridge::Render(void)
{

	const TEXINFO*		pTexture = CTextureMgr::GetInstance()->GetTexture(m_pObj->GetObjKey(), 
	m_wstrStateKey, (int)m_tFrame.fFrame);

	if(pTexture == NULL)
		return;

	float fX = pTexture->tImgInfo.Width / 2.f;
	float fY = pTexture->tImgInfo.Height / 2.f;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_pObj->GetInfo()->matWorld);
	CDevice::GetInstance()->GetSprite()->Draw(pTexture->pTexture, 
		NULL, &D3DXVECTOR3(fX, fY, 0.f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLongAttackBridge::Release(void)
{

}


void CLongAttackBridge::WorldMatrix(INFO& rInfo)
{
	
	D3DXMATRIX	matScale, matTrans;

	// 캐릭터 좌우 스케일링 계산
	if (rInfo.vDir.x < 0)
	{
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
	}
	else
	{
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	}

	// 캐릭터 y각도에 따라서 각도 전환
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



	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matScale * matTrans;
}

void CLongAttackBridge::Move(INFO &rInfo)
{

	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_UNIT);

	if (pPlayer == NULL)
		return;

	m_pObj->SetTargetPoint(((CPlayer*)pPlayer)->GetInfo()->vPos);

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);
	
		// 캐릭터 y각도에 따라서 각도 전환
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


	/*if(fDistance > 10.f)
	{*/
		rInfo.vPos += rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
	

	/*if(fDistance <= m_pObj->GetStat()->fRange)
	{
		m_pObj->SetOrder(OD_STAND);
	}

	if(rInfo.vPos == m_pObj->GetTargetPoint())
	{
		m_pObj->SetOrder(OD_STAND);
<<<<<<< HEAD
		SetFrame(L"Stand_1");
	}
=======
	}*/
}

void	CLongAttackBridge::SetAstar(D3DXVECTOR3 vTarget)
{
	m_vecBestList.clear();
	CAStar::GetInstance()->StartPos(m_pObj->GetInfo()->vPos, vTarget, &m_vecBestList);

}


void	CLongAttackBridge::AStarMove(INFO& rInfo)
{
	// 에이스타 오더를 받았을때만 이 무브를 사용함

	if(m_vecBestList.empty())
		return;

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();
	
	if(pVecTile == NULL)
		return;

	int		iMoveIndex = m_vecBestList.front();

	rInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - rInfo.vPos;
	float	fDistance = D3DXVec3Length(&rInfo.vDir);

	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// 캐릭터 y각도에 따라서 각도 전환
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
	{
		m_pObj->SetOrder(OD_STAND);
		SetFrame(L"Stand_1");
	}

}


void	CLongAttackBridge::Stop(INFO& rInfo)
{
	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_UNIT);

	if (pPlayer == NULL)
		return;

	m_pObj->SetTargetPoint(((CPlayer*)pPlayer)->GetInfo()->vPos);

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// 캐릭터 y각도에 따라서 각도 전환
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Stand_5";

	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Stand_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Stand_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Stand_3";

	else
		m_wstrStateKey = L"Stand_4";


}

void CLongAttackBridge::Back(INFO& rInfo)
{
	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_UNIT);

	if (pPlayer == NULL)
		return;
	m_pObj->SetTargetPoint(((CPlayer*)pPlayer)->GetInfo()->vPos);

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	// 캐릭터 y각도에 따라서 각도 전환
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

		rInfo.vPos -= rInfo.vDir * m_pObj->GetSpeed() * CTimeMgr::GetInstance()->GetTime();
}
void CLongAttackBridge::Attack(INFO& rInfo)
{
	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_UNIT);

	if (pPlayer == NULL)
		return;
	m_pObj->SetTargetPoint(((CPlayer*)pPlayer)->GetInfo()->vPos);

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);
	
		// 캐릭터 y각도에 따라서 각도 전환
	if (rInfo.vDir.y >= 0.75f)
		m_wstrStateKey = L"Attack_5";


	else if (rInfo.vDir.y >= 0.25f)
		m_wstrStateKey = L"Attack_1";

	else if (rInfo.vDir.y >= -0.25f)
		m_wstrStateKey = L"Attack_2";

	else if (rInfo.vDir.y >= -0.75f)
		m_wstrStateKey = L"Attack_3";

	else
		m_wstrStateKey = L"Attack_4";

}


void   CLongAttackBridge::ArtificiaIintelligence(INFO& rInfo)
{

	const CObj*	pPlayer = CObjMgr::GetInstance()->GetObj(OBJ_UNIT);

	if (pPlayer == NULL)
		return;

	m_pObj->SetTargetPoint(((CPlayer*)pPlayer)->GetInfo()->vPos);

	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	
	float fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);


	if(fDistance  <= m_pObj->GetStat()->fRange)//공격
	{
		m_pObj->SetOrder(OD_ATTACK);
	}

	if(fDistance >= m_pObj->GetStat()->fRange)//이동
	{
		//SetAstar(rInfo.vPos);
		m_pObj->SetOrder(OD_MOVE);
	}

	if(fDistance  <= m_pObj->GetStat()->fRange*2/3)//도망
	{
		m_pObj->SetOrder(OD_BACK);
	}
}
//
//
//void	CLongAttackBridge::Frame(void)
//{
//	m_tFrame.fFrame += m_tFrame.fCount * CTimeMgr::GetInstance()->GetTime();
//
//	if(m_tFrame.fFrame > m_tFrame.fMax)
//	{
//		switch (m_pObj->GetOrder())
//		{
//		case OD_STAND:
//			SetFrame(L"Stand_1");
//			break;
//
//		case OD_MOVE:
//			SetFrame(L"Walk_1");
//			break;
//
//		case OD_ASTAR:
//			SetFrame(L"Walk_1");
//			break;
//
//		case OD_PATROL:
//			SetFrame(L"Walk_1");
//			break;
//
//		case OD_ATTACK:
//			SetFrame(L"Stand_1");
//			m_pObj->SetOrder(OD_STAND);
//			break;
//
//		case OD_SKILL:
//			SetFrame(L"Stand_1");
//			m_pObj->SetOrder(OD_STAND);
//			break;
//
//		
//		}
//	}
//		
//}
