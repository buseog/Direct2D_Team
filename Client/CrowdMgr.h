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
	void	Release(void);
	void	Progress(void);
	vector<CObj*>*	GetSelectList(void);

private:
	CCrowdMgr(void);
	~CCrowdMgr(void);
};
