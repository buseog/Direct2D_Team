#pragma once
#include "item.h"

class CBelt :
	public CItem
{
public:
	CBelt(void);
	~CBelt(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
