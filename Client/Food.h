#pragma once
#include "item.h"

class CFood :
	public CItem
{
private:
	wstring			m_wstrStateKey;	
	
	
public:
	void WorldMatrix(void);

public:
	CFood(void);
	CFood(ITEM*	tItem);
	~CFood(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
