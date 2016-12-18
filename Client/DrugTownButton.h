#pragma once
#include "mybutton.h"

class CDrugTownButton :
	public CMyButton
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CDrugTownButton(void);
	~CDrugTownButton(void);
};
