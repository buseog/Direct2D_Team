#pragma once
#include "ui.h"

class CStatus :
	public CUi
{
private:
	bool		m_bKeyCheck;	// Ű üũ�� �ϱ� ���� �� ����

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CStatus(void);
	virtual ~CStatus(void);
};
