#pragma once
#include "item.h"


class CWeapon :
	public CItem
{
private:
	wstring			m_wstrStateKey;
	
//	
//public:
//	void WorldMatrix(void);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
//	virtual void Render(void);
	virtual void Release(void);


public:
	CWeapon(void);
	CWeapon(ITEM*	tItem);
	~CWeapon(void);

};