#pragma once

#include "Obj.h"
#include "Bigheader.h"
#include "Observer.h"

class CBridge;
class CUi :
	public	CObj
{
protected:
	static D3DXVECTOR3		m_vScroll;
	INFO					m_tInfo;
	wstring					m_wstrObjKey;
	CBridge*				m_pBridge;

	CObserver*				m_Observer;
	

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CUi(void);
	virtual ~CUi(void);
};
