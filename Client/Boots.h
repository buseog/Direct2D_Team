#pragma once
#include "item.h"

class CBoots :
	public CItem
{
public:
	CBoots(void);
	~CBoots(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
