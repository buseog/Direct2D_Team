#pragma once
#include "item.h"

class CEmptyItem :
	public CItem
{

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEmptyItem(void);
	~CEmptyItem(void);
};
