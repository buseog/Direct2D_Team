#pragma once

#include "Bigheader.h"

class CBridge;
class CObj
{
protected:
	static  D3DXVECTOR3		m_vScroll;
	CBridge*				m_pBridge;

	FRAME					m_tFrame;
	INFO					m_tInfo;
	
	bool					m_bDestroy;
	float					m_fScrollSpeed;
	wstring					m_wstrObjKey;
	

public:
	void	SetPos(const D3DXVECTOR3& vPos);
	void	SetPos(float fX, float fY);
	void	SetDestroy(bool	_YN);
	void	SetBridge(CBridge* pBridge);

public:
	CBridge*	GetBridge(void);
	const bool		GetDestroy(void);
	const INFO*		GetInfo(void) const;
	const wstring&	GetObjKey(void);

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
