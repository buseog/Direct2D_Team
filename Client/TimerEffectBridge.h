#pragma once
#include "effectbridge.h"

class CTimerEffectBridge :
	public CEffectBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);


public:
	void	EffectTime(void);

public:	
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);



public:
	CTimerEffectBridge(void);
	~CTimerEffectBridge(void);
};
