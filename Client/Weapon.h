#pragma once
#include "item.h"

class CWeapon :
	public CItem
{
public:
	CWeapon(void);
	~CWeapon(void);
public:
	virtual HRESULT Initialize(void);
	virtual int Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
