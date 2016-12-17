#pragma once
#include "Bigheader.h"

class CDevice;
class CSceneMgr;
class CMainGame
{
private:
	CDevice*		m_pDevice;
	CSceneMgr*		m_pSceneMgr;
	float			m_fTime;
	int				m_iCount;
	float           m_fMouseX;
	float           m_fMouseY;
	TCHAR			m_szFPS[MIN_STR];
	TCHAR			m_szMOUSEPOS[MIN_STR];
	D3DXMATRIX		m_matTrans;
	
public:
	HRESULT	Initialize(void);
	void	Progress(void);
	void	Render(void);
	void	Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
