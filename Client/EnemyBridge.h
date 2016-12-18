#pragma once
#include "objbridge.h"

class CEnemyBridge :
	public CObjBridge
{
private:
	list<int>		m_vecBestList;
	
	D3DXVECTOR3		m_vTargetPoint;
	D3DXVECTOR3		m_vOriginPoint;
	bool			m_bArrive;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

private:
	void	SetAstar(D3DXVECTOR3 vMouse);
	void	Move(INFO& rInfo);
	void	Patrol(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEnemyBridge(void);
	~CEnemyBridge(void);
};
