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

	void	SetStat(int _iIndex);	// 플레이어 스텟 

public:
	CPlayer(void);
	~CPlayer(void);
};
