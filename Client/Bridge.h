#pragma once
#include "BigHeader.h"

class CObj;
class CUi;
class CBridge
{
protected:
	CObj*		m_pObj;
	CUi*		m_pUi;
	wstring		m_wstrStateKey;
	float		m_fTime;
	FRAME		m_tFrame;
	int			m_iIndex;		// 은지 추가 - 피킹 처리 시 인덱스 값 구분

protected:
	virtual void	Frame(void);
	virtual void	WorldMatrix(INFO& rInfo) PURE;

public:
	void	SetObj(CObj* pObj);	
	void	SetUI(CUi*	pUi);
	void	SetFrame(const wstring& wstrStateKey);		//StateKey와 프레임값을 지정해주기 위한함수
	void	SetKey(const wstring& wstrStateKey);		//따로 셋키가 필요할때
	void	SetObjSize(void);							//Obj에 렉트 사이즈를 지정해주기 위한 함수
	void	SetUiSize(void);							//Ui에 렉트 사이즈를 지정해주기 위한 함수
	void	SetTime(float fTime);
	const	wstring&	GetStateKey(void);

public:
	virtual HRESULT	Initialize(void) PURE;
	virtual void	Progress(INFO& rInfo) PURE;
	virtual void	Render(void) PURE;
	virtual void	Release(void) PURE;
	virtual int		Picking(void);

public:
	CBridge(void);
	CBridge(CUi*	pUi);
	CBridge(CObj* pObj);
	virtual ~CBridge(void);
};
