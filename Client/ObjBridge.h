#pragma once
#include "bridge.h"
#include "Obj.h"

class CObjBridge :
	public CBridge
{
protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	void Die(void);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	
public:
	CObjBridge(void);
	CObjBridge(CObj* pObj);
	virtual ~CObjBridge(void);
};
