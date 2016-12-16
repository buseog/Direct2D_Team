#pragma once
#include "uibridge.h"

class CBattlePannelBridge :
	public CUiBridge
{
protected:
	virtual void		WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(void);

public:
	CBattlePannelBridge(void);
	~CBattlePannelBridge(void);
};
