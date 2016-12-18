#pragma once
#include "mybutton.h"

class CStoreButton :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
public:
	CStoreButton(void);
	~CStoreButton(void);
};
