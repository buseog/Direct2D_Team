#pragma once
#include "obj.h"

class CUnit :
	public CObj
{
protected:
	//UNITDATA					m_tUnit;
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	void    WorldMatrix(void);
	void    ScaleSync(void);

public:
	CUnit(void);
	CUnit(UNITDATA*	tUnit);
	virtual ~CUnit(void);
};
