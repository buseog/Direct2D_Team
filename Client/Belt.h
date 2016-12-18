#pragma once
#include "item.h"

class CBelt :
	public CItem
{
public:
	CBelt(void);
	CBelt(ITEM*	tItem);
	~CBelt(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
//	virtual void Render(void);
	virtual void Release(void);
};
