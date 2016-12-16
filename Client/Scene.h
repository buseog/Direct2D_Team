#pragma once

#include "Bigheader.h"
#include "Obj.h"
#include "Ui.h"
#include "SceneMgr.h"

class CScene
{
public:
	void			CreateBridge();

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

	virtual void	LoadPNG(void)PURE;

public:
	CScene(void);
	virtual ~CScene(void);
};
