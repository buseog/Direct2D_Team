#pragma once
#include "unit.h"

class CShortAttack :
	public CUnit
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CShortAttack(void);
	CShortAttack(UNITDATA*	tUnit);
	~CShortAttack(void);
};
