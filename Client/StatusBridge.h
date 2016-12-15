#pragma once
#include "uibridge.h"

class CStatusBridge :
	public CUiBridge
{

protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CStatusBridge(void);
	virtual ~CStatusBridge(void);
};
