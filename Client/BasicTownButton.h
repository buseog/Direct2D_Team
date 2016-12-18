#pragma once
#include "mybutton.h"

class CBasicTownButton :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CBasicTownButton(void);
	~CBasicTownButton(void);
};
