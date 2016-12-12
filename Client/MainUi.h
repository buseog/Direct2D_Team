#pragma once
#include "ui.h"

class CMainUi :
	public CUi
{

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CMainUi(void);
	virtual	~CMainUi(void);
};
