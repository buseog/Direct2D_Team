#pragma once
#include "Bigheader.h"

class CObj;
class CSKillMgr
{
public:
	static	void	Skill(D3DXVECTOR3 vPos, D3DXVECTOR3	vTarget, const wstring&	wstrName);
	static	void	ThunderField(D3DXVECTOR3 vPos);
	static	void	BlackHole(D3DXVECTOR3	vPos);
	static	void	IceBomb(D3DXVECTOR3	vPos);
	static	void	Blizzard(D3DXVECTOR3	vTarget);
public:
	CSKillMgr(void);
	~CSKillMgr(void);
};
