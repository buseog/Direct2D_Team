#pragma once

#include "Bigheader.h"

class CDevice
{
	DECLARE_SINGLETON(CDevice)

private:
	LPDIRECT3D9			m_p3D;
	LPDIRECT3DDEVICE9	m_pDevice;
	LPD3DXSPRITE		m_pSprite;
	LPD3DXFONT			m_pFont;
	LPD3DXFONT			m_pLoadingFont;
	LPD3DXFONT			m_pUIFont;
	LPD3DXLINE			m_pLine;

public:
	HRESULT		InitDevice(void);
	void		Release(void);

	void		Render_Begin(void);
	void		Render_End();

public:
	LPDIRECT3DDEVICE9 GetDevice(void);
	LPD3DXSPRITE	  GetSprite(void);
	LPD3DXFONT		  GetFont(void);
	LPD3DXFONT		  GetLoadingFont(void);
	LPD3DXFONT		  GetUIFont(void);
	LPD3DXLINE		  GetLine(void);

private:
	void	SetParameters(D3DPRESENT_PARAMETERS& d3dpp);

private:
	CDevice(void);
	~CDevice(void);
};
