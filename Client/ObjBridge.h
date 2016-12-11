#pragma once
#include "bridge.h"

class CObjBridge :
	public CBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CObjBridge(void);
	CObjBridge(CObj* pObj);
	~CObjBridge(void);
};
