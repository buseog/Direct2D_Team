#pragma once
#include "item.h"

class CFood :
	public CItem
{
public:
	CFood(void);
	~CFood(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
