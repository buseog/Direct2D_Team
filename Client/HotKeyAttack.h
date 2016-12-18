#pragma once
#include "mybutton.h"

class CHotKeyAttack :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CHotKeyAttack(void);
	~CHotKeyAttack(void);
};
