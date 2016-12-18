#pragma once
#include "scene.h"

class CBattleField :
	public CScene
{
private:
	list<CObj*>*		m_ObjList[OBJ_END];

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	LoadPNG(void);

public:
	CBattleField(void);
	~CBattleField(void);
};
