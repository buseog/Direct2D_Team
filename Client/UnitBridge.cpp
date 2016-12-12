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
	KeyInput(rInfo);
	Frame();
	Move(rInfo);

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
	if(GetAsyncKeyState(VK_RBUTTON))
	{
		D3DXVECTOR3 vMouse = ::GetMouse() - m_pObj->GetScroll();
		CAStar::GetInstance()->StartPos(rInfo.vPos, vMouse);
	}
}

void	CUnitBridge::Move(INFO& rInfo)
{
	list<int>*		pBestList = CAStar::GetInstance()->GetBestList();
	if(pBestList->empty())
		return;

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();

	if(pVecTile == NULL)
		return;

	int		iMoveIndex = pBestList->front();

	rInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - rInfo.vPos;
	float	fDistance = D3DXVec3Length(&rInfo.vDir);

	D3DXVec3Normalize(&rInfo.vDir, &rInfo.vDir);

	rInfo.vPos += rInfo.vDir * 300 * CTimeMgr::GetInstance()->GetTime();

	if(fDistance < 10.f)
	{
		pBestList->pop_front();
	}
}