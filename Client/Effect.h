#pragma once
#include "obj.h"

class CEffect :
	public CObj
{

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
	virtual const RECT			GetRect(void);	

public:
	CEffect(void);
	~CEffect(void);
};
