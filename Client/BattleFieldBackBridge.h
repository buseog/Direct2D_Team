#pragma once
#include "backbridge.h"

class CBattleFieldBackBridge :
	public CBackBridge
{
private:
	RECT				m_rcDrag;
	D3DXVECTOR2			m_vDrag[5];
	int					m_iDragState;

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int	Picking(void);

public:
	CBattleFieldBackBridge(void);
	~CBattleFieldBackBridge(void);
};
