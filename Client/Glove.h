#pragma once
#include "item.h"

class CGlove :
	public CItem
{
public:
	CGlove(void);
	~CGlove(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
