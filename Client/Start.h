#pragma once
#include "scene.h"

class CStart :
	public CScene
{
private:
	HANDLE				m_hThread;
	CRITICAL_SECTION	m_Crt;
	int					m_iMaxLoad;

public:
	static unsigned int __stdcall ImgLoadThreadFunc(void*	pArg);
	CRITICAL_SECTION	GetCrt(void);

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
