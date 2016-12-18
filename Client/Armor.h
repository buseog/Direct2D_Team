#pragma once
#include "item.h"

class CArmor :
	public CItem
{

private:
	wstring			m_wstrStateKey;	

public:
	CArmor(void);
	CArmor(ITEM*	tItem);
	~CArmor(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Release(void);
};
