#pragma once
#include "backbridge.h"

class CVillageBackBridge :
	public CBackBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CVillageBackBridge(void);
	~CVillageBackBridge(void);
};
