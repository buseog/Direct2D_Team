#include "StdAfx.h"
#include "AStar.h"
#include "ObjMgr.h"

IMPLEMENT_SINGLETON(CAStar)

CAStar::CAStar(void)
{
}

CAStar::~CAStar(void)
{
	Release();
}
void CAStar::AStarStart(const int& iStartIndex, const int& iGoalIndex)
{
	if(iStartIndex == iGoalIndex)
		return;

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();

	if(pVecTile == NULL)
		return;

	if((*pVecTile)[iGoalIndex]->byOption == 1)
		return;

	Release();

	MakeRoute();
}

void CAStar::Release(void)
{
	for_each(m_OpenList.begin(), m_OpenList.end(), DeleteObj());
	m_OpenList.clear();

	for_each(m_CloseList.begin(), m_CloseList.end(), DeleteObj());
	m_CloseList.clear();

	m_BestList.clear();
}

void CAStar::MakeRoute(void)
{
	NODE*		pParent = new NODE;

	pParent->iIndex  = m_iStartIndex;
	pParent->pParent = NULL;
	pParent->fCost   = 0.f;

	m_CloseList.push_back(pParent);			// 검색 대상에서 제외

	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();

	if(pVecTile == NULL)
		return;

	NODE*		pNode = NULL;
	int			iIndex = 0;

	while(true)
	{
		for (list<int>::iterator listiter = (*pVecTile)[pParent->iIndex]->Connectlist.begin();
			listiter != (*pVecTile)[pParent->iIndex]->Connectlist.end(); ++listiter)
		{
			if ((*pVecTile)[pParent->iIndex]->byOption == 0)
			{
				pNode = CreateNode(*listiter, pParent, pVecTile);
				m_OpenList.push_back(pNode);
			}
		}

		m_OpenList.sort(Compare);

		list<NODE*>::iterator		iter = m_OpenList.begin();

		pParent = *iter;
		
		m_CloseList.push_back(*iter);
		m_OpenList.erase(iter);

		if(pParent->iIndex == m_iGoalIndex)
		{
			while(true)
			{
				m_BestList.push_back(pParent->iIndex);
				pParent = pParent->pParent;

				if(pParent->iIndex == m_iStartIndex)
					break;
			}

			m_BestList.reverse();

			break;
		}

	}

}

bool CAStar::CheckList(const int& iIndex)
{
	for(list<NODE*>::iterator	iter = m_OpenList.begin();
		iter != m_OpenList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	for(list<NODE*>::iterator	iter = m_CloseList.begin();
		iter != m_CloseList.end(); ++iter)
	{
		if((*iter)->iIndex == iIndex)
			return false;
	}

	return true;
}

NODE* CAStar::CreateNode(int iIndex, NODE* pParent, const vector<TILE2*>* pTile)
{
	NODE*	pNode = new NODE;

	pNode->iIndex  = iIndex;
	pNode->pParent = pParent;
	
	D3DXVECTOR3		vDistance = (*pTile)[iIndex]->vPos - (*pTile)[pParent->iIndex]->vPos;
	float			fPCost = D3DXVec3Length(&vDistance);

	vDistance = (*pTile)[iIndex]->vPos -(*pTile)[m_iGoalIndex]->vPos;
	float			fGCost = D3DXVec3Length(&vDistance);	
	
	pNode->fCost   = fPCost + fGCost;

	return pNode;
}

bool CAStar::Compare(const NODE* pTemp, const NODE* pDest)
{
	return pTemp->fCost < pDest->fCost;
}

void CAStar::StartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos)
{
	m_iStartIndex = GetTileIndex(vStartPos);
	m_iGoalIndex = GetTileIndex(vGoalPos);

	if (m_iGoalIndex < 0 || m_iGoalIndex >= TILEX * TILEY)
		return;

	AStarStart(m_iStartIndex, m_iGoalIndex);
}

int CAStar::GetTileIndex(const D3DXVECTOR3& vPos)
{
	const vector<TILE2*>*	pVecTile = CObjMgr::GetInstance()->GetTile();

	if(pVecTile == NULL)
		return -1;

	for(size_t i = 0; i < pVecTile->size(); ++i)
	{
		if (Picking(vPos, (*pVecTile)[i]))
		{
			return i;
		}
	}

	return -1;
}

bool CAStar::Picking(const D3DXVECTOR3& vPos, const TILE2* pTile)
{

	D3DXVECTOR3		vPoint[4] = 
	{
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y - TILECY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x + TILECX / 2.f, pTile->vPos.y, 0.f),
		D3DXVECTOR3(pTile->vPos.x, pTile->vPos.y + TILECY / 2.f, 0.f),
		D3DXVECTOR3(pTile->vPos.x - TILECX / 2.f, pTile->vPos.y, 0.f)
	}; 

	D3DXVECTOR3		vDirection[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};


	D3DXVECTOR3		vNormal[4] = 
	{
		D3DXVECTOR3(vDirection[0].y, -vDirection[0].x, 0.f),
		D3DXVECTOR3(vDirection[1].y, -vDirection[1].x, 0.f),
		D3DXVECTOR3(vDirection[2].y, -vDirection[2].x, 0.f),
		D3DXVECTOR3(vDirection[3].y, -vDirection[3].x, 0.f)
	};

	for(int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for(int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3		vDestDir = vPos - vPoint[i];
		D3DXVec3Normalize(&vDestDir, &vDestDir);

		float fDotResult = D3DXVec3Dot(&vDestDir, &vNormal[i]);

		if(fDotResult > 0.f)
			return false;
	}

	return true;
}

list<int>* CAStar::GetBestList(void)
{
	return &m_BestList;
}
