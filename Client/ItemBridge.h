#pragma once
#include "bridge.h"

class CItemBridge :
	public CBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CItemBridge(void);
	CItemBridge(CUi*	pItem);
	virtual ~CItemBridge(void);
};
