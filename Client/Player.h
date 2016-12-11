#pragma once
#include "obj.h"

class CPlayer :
	public CObj
{
public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CPlayer(void);
	~CPlayer(void);
};
