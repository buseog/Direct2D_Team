#pragma once
#include "item.h"

class CArmor :
	public CItem
{
public:
	CArmor(void);
	~CArmor(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
