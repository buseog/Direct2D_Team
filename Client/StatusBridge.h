#pragma once
#include "uibridge.h"
#include "Player.h"

class CUi;
class CStatusBridge :
	public CUiBridge
{
protected:
	virtual void		WorldMatrix(INFO& rInfo);
	vector<CUi*>		m_vecButton;

public:
	vector<CUi*>*		GetButton(void);
	CPlayer*			m_pPlayer;

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(INFO& rInfo);

public:
	CStatusBridge(void);
	virtual ~CStatusBridge(void);
};
