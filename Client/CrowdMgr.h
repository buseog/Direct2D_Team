#pragma once
#include "Bigheader.h"

class CObj;

class CCrowdMgr
{
	DECLARE_SINGLETON(CCrowdMgr)

private:
	vector<CObj*>	m_vecSelectUnit;
	int				m_iAstarCount;
	int				m_iLimit;
	bool			m_bStart;

public:
	void	AddSelectList(CObj*	pObj);
	vector<CObj*>*	GetSelectList(void);
	void	RenderPortrait(void);
	void	KeyInput(void);

public:
	void	Release(void);
	void	Progress(void);

private:
	CCrowdMgr(void);
	~CCrowdMgr(void);
};
