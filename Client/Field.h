#pragma once
#include "scene.h"

class CUI;
class CObj;
class CField :
	public CScene
{
private:
	bool	m_bStage;

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(void);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual void	LoadPNG(void);

public:
	CField(void);
	~CField(void);
};
