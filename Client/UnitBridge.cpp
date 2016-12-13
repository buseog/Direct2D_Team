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
	Frame();
	

	switch (m_pObj->GetOrder())
	{
	case OD_ASTAR:
		AStarMove(rInfo);
		break;
	case OD_MOVE:
		Move(rInfo);
		break;
	}

	KeyInput(rInfo);

}

void CUnitBridge::Render(void)
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

void CUnitBridge::Release(void)
{
	
}

void	CUnitBridge::WorldMatrix(INFO& rInfo)
{
	D3DXMATRIX	matTrans;

	D3DXMatrixTranslation(&matTrans, 
		rInfo.vPos.x + m_pObj->GetScroll().x, 
		rInfo.vPos.y + m_pObj->GetScroll().y, 
		0.f);

	rInfo.matWorld = matTrans;
}

void	CUnitBridge::KeyInput(INFO& rInfo)
{
	
}

void	CUnitBridge::Move(INFO& rInfo)
{
	rInfo.vDir = m_pObj->GetTargetPoint() - rInfo.vPos;
	float	fDistance = D3DXVec3Length(&rInfo.vDir);
	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	if(fDistance > 10.f)
	{
		rInfo.vPos += rInfo.vDir * 300 * CTimeMgr::GetInstance()->GetTime();
	}

}

void	CUnitBridge::SetAstar(D3DXVECTOR3 vMouse)
{
	m_vecBestList.clear();
	CAStar::GetInstance()->StartPos(m_pObj->GetInfo()->vPos, vMouse, &m_vecBestList);
}

void	CUnitBridge::AStarMove(INFO& rInfo)
{
	if(m_vecBestList.empty())
		return;

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();
	
	if(pVecTile == NULL)
		return;

	int		iMoveIndex = m_vecBestList.front();

	rInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - rInfo.vPos;
	float	fDistance = D3DXVec3Length(&rInfo.vDir);

	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	rInfo.vPos += rInfo.vDir * 300 * CTimeMgr::GetInstance()->GetTime();

	if(fDistance < 10.f)
	{
		m_vecBestList.pop_front();
	}
}