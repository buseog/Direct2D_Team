#pragma once
#include "objbridge.h"

class CEnemyBridge :
	public CObjBridge
{
private:
	list<int>		m_vecBestList;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

private:
	void	SetAstar(D3DXVECTOR3 vMouse);
	void	KeyInput(INFO& rInfo);
	void	Move(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEnemyBridge(void);
	~CEnemyBridge(void);
};
