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
	void	SetAttack(int _iAttack);


public:
	CPlayer(void);
	~CPlayer(void);
};
