#pragma once
#include "bridge.h"

class CUiBridge :
	public CBridge
{
protected:
	int		m_iPriority;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CUiBridge(void);
	CUiBridge(CUi*	pUi);
	virtual ~CUiBridge(void);
};
