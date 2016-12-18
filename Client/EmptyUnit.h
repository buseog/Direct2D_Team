#pragma once
#include "Unit.h"

class CEmptyUnit :
	public CUnit
{

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CEmptyUnit(void);
	~CEmptyUnit(void);
};
