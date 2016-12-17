#pragma once
#include "observer.h"

class CUIObserver :
	public CObserver
{
private:
	UNITDATA			m_tData;
	D3DXMATRIX			m_matPlayer;

public:
	CUIObserver(void);
	virtual ~CUIObserver(void);

public:
	virtual void Update(int iFlag, void* pData);

public:
	const UNITDATA*		GetData(void);
	const D3DXMATRIX*	GetMatrix(void);

};
