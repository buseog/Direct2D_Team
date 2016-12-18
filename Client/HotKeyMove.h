#pragma once
#include "mybutton.h"

class CHotKeyMove :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CHotKeyMove(void);
	~CHotKeyMove(void);
};
