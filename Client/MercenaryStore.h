#pragma once
#include "store.h"

class CMercenaryStore :
	public CStore
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CMercenaryStore(void);
	~CMercenaryStore(void);
};
