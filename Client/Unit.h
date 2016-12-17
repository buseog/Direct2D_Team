#pragma once
#include "obj.h"

class CUnit :
	public CObj
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CUnit(void);
	virtual ~CUnit(void);
};
