#pragma once
#include "observer.h"

class CUIObserver :
	public CObserver
{
private:
	UNITDATA			m_tData;
	int					m_iIndex;

public:
	CUIObserver(void);
	virtual ~CUIObserver(void);

public:
	virtual void Update(void);
	void	SetIndex(int iIndex);

public:
	const UNITDATA*		GetData(void);
};
