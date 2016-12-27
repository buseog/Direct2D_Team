#pragma once
#include "backbridge.h"

class CUi;
class CFieldBackBridge :
	public CBackBridge
{
private:
	vector<CUi*>	m_vecPortrait;
	bool	m_bStage;
	float	m_fTime;
	CObj*	m_pPick;
	wstring m_strMonsterKey;

public:
	void	BattleWait(void);
	void	InitPortrait(void);



public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(void);

public:
	CFieldBackBridge(void);
	~CFieldBackBridge(void);
};
