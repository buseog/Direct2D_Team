#pragma once
#include "buttonbridge.h"

class CMercenaryBridge :
	public CButtonBridge
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	WorldMatrix(INFO& rInfo);

public: // ¸Ê Ã¼Å©  
	int		m_iMapKey;
	
	void	SetMapKey(int _iKey);
	virtual int		Picking(void);

public:
	CMercenaryBridge(void);
	~CMercenaryBridge(void);
};
