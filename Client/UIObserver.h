#pragma once
#include "observer.h"

class CUIObserver :
	public CObserver
{
private:
	UNITDATA			m_tData;

public:
	CUIObserver(void);
	virtual ~CUIObserver(void);

public:
	virtual void Update(int iFlag, void* pData);

public:
	const UNITDATA*		GetData(void);
};
