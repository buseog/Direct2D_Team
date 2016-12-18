#pragma once
#include "mybutton.h"

class CTownButton :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CTownButton(void);
	~CTownButton(void);
};
