#pragma once
#include "Scene.h"

class CVillage	:
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	LoadPNG(void);

public:
	CVillage(void);
	~CVillage(void);
};
