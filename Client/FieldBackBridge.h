#pragma once
#include "backbridge.h"

class CFieldBackBridge :
	public CBackBridge
{
private:
	bool	m_bStage;

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
