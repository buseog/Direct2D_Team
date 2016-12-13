#pragma once
#include "item.h"

class CHelmet :
	public CItem
{
public:
	CHelmet(void);
	~CHelmet(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
