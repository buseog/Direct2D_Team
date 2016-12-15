#pragma once
#include "effectbridge.h"

class CStandEffectBridge :
	public CEffectBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	Frame(void);

public:
	CStandEffectBridge(void);
	~CStandEffectBridge(void);
};
