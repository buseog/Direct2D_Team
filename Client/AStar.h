#pragma once

#include "Include.h"

class CAStar
{
	DECLARE_SINGLETON(CAStar)

private:
	list<NODE*>			m_OpenList;
	list<NODE*>			m_CloseList;
	list<int>			m_BestList;

	int					m_iStartIndex;
	int					m_iGoalIndex;

public:
	void	AStarStart(const int& iStartIndex, const int& iGoalIndex);
	void	Release(void);

	void	MakeRoute(void);
	bool	CheckList(const int& iIndex);
	NODE*	CreateNode(int iIndex, NODE* pParent, const vector<TILE*>* pTile);
	static bool	Compare(const NODE* pTemp, const NODE* pDest);

	void	StartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos);
	int		GetTileIndex(const D3DXVECTOR3& vPos);
	bool	Picking(const D3DXVECTOR3& vPos, const TILE* pTile);

	list<int>*		GetBestList(void);

private:
	CAStar(void);
	~CAStar(void);
};
