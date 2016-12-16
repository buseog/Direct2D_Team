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
	void	SetFrame(const wstring& wstrStateKey);		//StateKey와 프레임값을 지정해주기 위한함수
	void	SetKey(const wstring& wstrStateKey);		//따로 셋키가 필요할때
	void	SetObjSize(void);							//Obj에 렉트 사이즈를 지정해주기 위한 함수


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
