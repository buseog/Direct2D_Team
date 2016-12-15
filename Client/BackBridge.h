#pragma once
#include "objbridge.h"

class CBackBridge :
	public CObjBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CBackBridge(void);
	virtual ~CBackBridge(void);
};
