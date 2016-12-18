#pragma once
#include "mybutton.h"

class CMercenaryTownButton :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMercenaryTownButton(void);
	~CMercenaryTownButton(void);
};
