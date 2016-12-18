#pragma once
#include "backbridge.h"

class CBattleFieldBackBridge :
	public CBackBridge
{
private:
	RECT				m_rcDrag;
	D3DXVECTOR2			m_vDrag[5];
	int					m_iDragState;
	list<CObj*>*		m_ObjList[OBJ_END];
	bool	m_bStage;
	float	m_fTime;

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
