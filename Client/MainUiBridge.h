#pragma once
#include "uibridge.h"

class CMainUiBridge :
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
	CMainUiBridge(void);
	virtual ~CMainUiBridge(void);
};
