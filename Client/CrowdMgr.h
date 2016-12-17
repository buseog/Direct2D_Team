#pragma once
#include "Bigheader.h"

class CObj;
class CUi;

class CCrowdMgr
{
	DECLARE_SINGLETON(CCrowdMgr)

private:
	vector<CObj*>	m_vecSelectUnit;
	vector<CUi*>	m_vecPortrait;
	int				m_iAstarCount;
	int				m_iLimit;
	bool			m_bStart;

public:
	void	AddSelectList(CObj*	pObj);
	int		GetSelectList(void);
	void	RenderPortrait(void);
	void	KeyInput(void);
	void	Clear(void);

public:
	void	Release(void);
	void	Progress(void);

private:
	CCrowdMgr(void);
	~CCrowdMgr(void);
};
