#pragma once

#include "Bigheader.h"
#include "Bridge.h"


class CUi
{
protected:
	static D3DXVECTOR3		m_vScroll;
	INFO					m_tInfo;
	wstring					m_wstrObjKey;
	CBridge*				m_pBridge;
	bool					m_bView;


public:
	const INFO*		GetInfo(void) const;
	void			SetPos(const D3DXVECTOR3& vPos);
	void			SetPos(float fX, float fY);
	void			SetBridge(CBridge* pBridge);
	const wstring&	GetObjKey(void);
	const RECT		GetRect(void);
	int				Picking(void);

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;


public:
	CUi(void);
	virtual ~CUi(void);
};
