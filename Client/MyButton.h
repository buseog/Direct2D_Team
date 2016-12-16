#pragma once
#include "ui.h"

class CMyButton :
	public CUi
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMyButton(void);
	~CMyButton(void);
};
