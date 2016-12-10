#pragma once

#include "Obj.h"

class CBridge
{
protected:
	CObj*		m_pObj;
	wstring		m_wstrStateKey;
	FRAME		m_tFrame;

public:
	void		SetObj(CObj* pObj);
	void	SetFrame(const wstring& wstrStateKey);

public:
	virtual HRESULT	Initialize(void) PURE;
	virtual void	Progress(void) PURE;
	virtual void	Render(void) PURE;
	virtual void	Release(void) PURE;

public:
	CBridge(void);
	CBridge(CObj* pObj);
	virtual ~CBridge(void);
};
