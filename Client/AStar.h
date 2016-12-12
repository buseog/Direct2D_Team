#pragma once

#include "Bigheader.h"

class CAStar
{
	DECLARE_SINGLETON(CAStar)

private:
	multimap<float, NODE*>		m_OpenMap;
	list<NODE*>			m_CloseList;
	list<int>*			m_pBestList;
	vector<bool>		m_bCheck;

	int					m_iStartIndex;
	int					m_iGoalIndex;

public:
	void	AStarStart(const int& iStartIndex, const int& iGoalIndex);
	void	Release(void);

	void	MakeRoute(void);
	NODE*	CreateNode(int iIndex, NODE* pParent, const vector<TILE2*>* pTile);

	void	StartPos(const D3DXVECTOR3& vStartPos, const D3DXVECTOR3& vGoalPos, list<int>* pBestList);
	int		GetTileIndex(const D3DXVECTOR3& vPos);
	bool	Picking(const D3DXVECTOR3& vPos, const TILE2* pTile);

private:
	CAStar(void);
	~CAStar(void);
};
