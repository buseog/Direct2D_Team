#pragma once
#include "objbridge.h"

class CUnitBridge :
	public CObjBridge
{
private:
	void	KeyInput(INFO& rInfo);
	void	Move(INFO& rInfo);

protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CUnitBridge(void);
	virtual ~CUnitBridge(void);
};
