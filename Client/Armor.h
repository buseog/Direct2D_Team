#pragma once
#include "item.h"

class CArmor :
	public CItem
{

private:
	wstring			m_wstrStateKey;	
	
public:
	void WorldMatrix(void);

public:
	CArmor(void);
	~CArmor(void);
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);
};
