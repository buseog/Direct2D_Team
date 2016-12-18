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
	int		KeyInput(void);
	void	Clear(void);

public:
	void	Release(void);
	int		Progress(void);

public: // 단축키 관련 - 은지 추가
	void	HotKeyCheck(void);
	int	Picking(void);

	int		m_iPButtonCheck;;
	vector<CUi*>	m_HotButton;

private:
	CCrowdMgr(void);
	~CCrowdMgr(void);
};
