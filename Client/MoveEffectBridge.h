#pragma once
#include "effectbridge.h"

class CMoveEffectBridge :
	public CEffectBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CMoveEffectBridge(void);
	~CMoveEffectBridge(void);
};
