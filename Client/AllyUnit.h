#pragma once
#include "unit.h"

class CAllyUnit :
	public CUnit
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CAllyUnit(void);
	CAllyUnit(UNITDATA*	tUnit);
	~CAllyUnit(void);
};
