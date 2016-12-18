#pragma once
#include "objbridge.h"

class CLongAttackBridge :
	public CObjBridge
{
private:
	list<int>		m_vecBestList;

protected:
	virtual void	WorldMatrix(INFO& rInfo);

private:
	void	Move(INFO& rInfo);
	void	Stop(INFO& rInfo);
	void	Attack(INFO& rInfo);
	void	AStarMove(INFO& rInfo);

public:	
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CLongAttackBridge(void);
	~CLongAttackBridge(void);
};
