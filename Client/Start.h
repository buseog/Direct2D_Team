#pragma once
#include "scene.h"

class CStart :
	public CScene
{
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	LoadPNG(void);

public:
	CStart(void);
	~CStart(void);
};
