#pragma once
#include "ui.h"
#include "Observer.h"

class CPortrait :
	public CUi
{
private:
	CObserver*	m_pObserver;
	UNITDATA	m_tData;

public:
	CObserver*	GetObserver(void);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CPortrait(void);
	~CPortrait(void);
};
