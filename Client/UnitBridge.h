#pragma once
#include "objbridge.h"

class CUnitBridge :
	public CObjBridge
{
private:
	list<int>		m_vecBestList;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

private:
	void	KeyInput(INFO& rInfo);
	void	Move(INFO& rInfo);
	void	AStarMove(INFO& rInfo);
	void	Attack(INFO& rInfo);
	void	Stop(INFO& rInfo);
	void	Patrol(INFO& rInfo);
	void	Skill(INFO&	rInfo);

public:
	void	SetAstar(D3DXVECTOR3 vMouse);
	
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual	void	Frame(void);

public:
	CUnitBridge(void);
	virtual ~CUnitBridge(void);
};
