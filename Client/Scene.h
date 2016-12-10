#pragma once

#include "Bigheader.h"

class CScene
{
public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};
