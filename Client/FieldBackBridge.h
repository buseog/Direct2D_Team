#pragma once
#include "backbridge.h"

class CFieldBackBridge :
	public CBackBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void		Picking(void);

public:
	CFieldBackBridge(void);
	~CFieldBackBridge(void);
};
