#pragma once
#include "ui.h"

class CStore :
	public CUi
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CStore(void);
	virtual ~CStore(void);
};
