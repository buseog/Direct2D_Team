#pragma once

class CObj;
class CUi;
class CBridge
{
protected:
	CObj*		m_pObj;
	CUi*		m_pUi;
	wstring		m_wstrStateKey;
	FRAME		m_tFrame;

protected:
	virtual void	Frame(void);
	virtual void	WorldMatrix(INFO& rInfo) PURE;

public:
	void	SetObj(CObj* pObj);
	void	SetUI(CUi*	pUi);
	void	SetFrame(const wstring& wstrStateKey);
	void	SetKey(const wstring& wstrStateKey);


public:
	virtual HRESULT	Initialize(void) PURE;
	virtual void	Progress(INFO& rInfo) PURE;
	virtual void	Render(void) PURE;
	virtual void	Release(void) PURE;

public:
	CBridge(void);
	CBridge(CUi*	pUi);
	CBridge(CObj* pObj);
	virtual ~CBridge(void);
};
