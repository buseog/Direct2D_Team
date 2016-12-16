#pragma once
#include "ui.h"

class CItem;
class CInventory :
	public CUi
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CInventory(void);
	virtual ~CInventory(void);
};
