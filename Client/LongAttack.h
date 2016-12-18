#pragma once
#include "unit.h"

class CLongAttack :
	public CUnit
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CLongAttack(void);
	CLongAttack(UNITDATA*	tUnit);
	~CLongAttack(void);
};
