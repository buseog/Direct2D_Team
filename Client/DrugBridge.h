#pragma once
#include "buttonbridge.h"

class CDrugBridge :
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
	CDrugBridge(void);
	~CDrugBridge(void);
};
