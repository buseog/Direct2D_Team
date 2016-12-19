#pragma once
#include "backbridge.h"

class CInVillageBackBridge :
	public CBackBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CInVillageBackBridge(void);
	~CInVillageBackBridge(void);
};
