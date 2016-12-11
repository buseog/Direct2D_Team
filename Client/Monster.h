#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMonster(void);
	~CMonster(void);
};
