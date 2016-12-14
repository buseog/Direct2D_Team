#pragma once
#include "objbridge.h"

class CEffectBridge :
	public CObjBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEffectBridge(void);
	virtual ~CEffectBridge(void);
};
