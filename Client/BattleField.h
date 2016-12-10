#pragma once
#include "scene.h"

class CBattleField :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CBattleField(void);
	~CBattleField(void);
};
