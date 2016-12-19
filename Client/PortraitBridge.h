#pragma once
#include "uibridge.h"

class CPortraitBridge :
	public CUiBridge
{
protected:
	int		m_iIndex;
	int		m_iType;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	void	SetIndex(int iIndex);
	void	SetType(int iType);

public:
	int		GetIndex(void);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CPortraitBridge(void);
	~CPortraitBridge(void);
};
