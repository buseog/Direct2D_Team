#pragma once
#include "bridge.h"

class CUiBridge :
	public CBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CUiBridge(void);
	CUiBridge(CObj*	pObj);
	virtual ~CUiBridge(void);
};
