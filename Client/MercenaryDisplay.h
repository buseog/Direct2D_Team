#pragma once
#include "ui.h"

class CMercenaryDisplay :
	public CUi
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CMercenaryDisplay(void);
	virtual ~CMercenaryDisplay(void);
};
