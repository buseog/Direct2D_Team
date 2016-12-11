#pragma once
#include "Bigheader.h"

class CDevice;
class CSceneMgr;
class CMainGame
{
private:
	CDevice*		m_pDevice;
	CSceneMgr*		m_pSceneMgr;
	

public:
	HRESULT	Initialize(void);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
