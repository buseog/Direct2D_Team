#pragma once
#include "ui.h"

class CStatus :
	public CUi
{
private:
	bool		m_bKeyCheck;	// 키 체크를 하기 위한 불 변수

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CStatus(void);
	virtual ~CStatus(void);
};
