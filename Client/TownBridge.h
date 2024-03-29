#pragma once
#include "buttonbridge.h"

class CTownBridge :
	public CButtonBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	WorldMatrix(INFO& rInfo);

public: // �� üũ  
	int		m_iMapKey;
	
	void	SetMapKey(int _iKey);
	virtual int		Picking(void);

public:
	CTownBridge(void);
	~CTownBridge(void);
};
