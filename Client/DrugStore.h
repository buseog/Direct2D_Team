#pragma once
#include "store.h"

class CDrugStore :
	public CStore
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CDrugStore(void);
	~CDrugStore(void);
};
