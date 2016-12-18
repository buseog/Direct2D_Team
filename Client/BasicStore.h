#pragma once
#include "store.h"

class CBasicStore :
	public CStore
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CBasicStore(void);
	~CBasicStore(void);
};
