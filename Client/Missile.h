#pragma once
#include "obj.h"

class CMissile :
	public CObj
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMissile(void);
	~CMissile(void);
};
