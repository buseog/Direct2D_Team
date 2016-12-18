#pragma once
#include "mybutton.h"

class CHotKeyStop :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CHotKeyStop(void);
	~CHotKeyStop(void);
};
