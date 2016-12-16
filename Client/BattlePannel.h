#pragma once
#include "Ui.h"

class CBattlePannel	:
	public	CUi
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CBattlePannel(void);
	~CBattlePannel(void);
};
