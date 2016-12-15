#pragma once
#include "objbridge.h"

class CEffectBridge :
	public CObjBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEffectBridge(void);
	virtual ~CEffectBridge(void);
};
