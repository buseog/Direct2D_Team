#pragma once
#include "Bigheader.h"

class CObj;
class CSKillMgr
{
public:
	static	CObj*	Skill(D3DXVECTOR3 vPos, D3DXVECTOR3	vTarget, const wstring&	wstrName);

public:
	CSKillMgr(void);
	~CSKillMgr(void);
};
