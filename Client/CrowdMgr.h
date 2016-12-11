#pragma once
#include "Bigheader.h"

class CObj;

class CCrowdMgr
{
	DECLARE_SINGLETON(CCrowdMgr)

private:
	vector<CObj*>	m_vecSelectUnit;

public:
	void	Release(void);

private:
	CCrowdMgr(void);
	~CCrowdMgr(void);
};