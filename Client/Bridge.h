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
	int			m_iIndex;		// ���� �߰� - ��ŷ ó�� �� �ε��� �� ����

protected:
	virtual void	Frame(void);
	virtual void	WorldMatrix(INFO& rInfo) PURE;

public:
	void	SetObj(CObj* pObj);	
	void	SetUI(CUi*	pUi);
	void	SetFrame(const wstring& wstrStateKey);		//StateKey�� �����Ӱ��� �������ֱ� �����Լ�
	void	SetKey(const wstring& wstrStateKey);		//���� ��Ű�� �ʿ��Ҷ�
	void	SetObjSize(void);							//Obj�� ��Ʈ ����� �������ֱ� ���� �Լ�
	void	SetUiSize(void);							//Ui�� ��Ʈ ����� �������ֱ� ���� �Լ�
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
