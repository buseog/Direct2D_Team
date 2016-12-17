#pragma once
#include "unit.h"

class CEnemyUnit :
	public CUnit
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEnemyUnit(void);
	~CEnemyUnit(void);
};
