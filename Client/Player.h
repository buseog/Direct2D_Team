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
	void	SetPlusAttack(int _iAttack); // 장비착용후 공격력 증가
	void	SetPlusDefence(int _iDefence); // 장비착용후 방어력 증가
	void	SetMinusAttack(int _iAttack); // 장비착용후 공격력 감소
	void	SetMinusDefence(int _iDefence); // 장비착용후 방어력 감소


public:
	CPlayer(void);
	~CPlayer(void);
};
