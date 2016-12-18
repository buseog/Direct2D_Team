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

	int		GetHP(void);
	int		GetMaxHP(void);

	void	SetStat(int _iIndex);	// 플레이어 스텟 
	void	SetPlusAttack(int _iAttack); // 장비착용후 공격력 증가
	void	SetPlusDefence(int _iDefence); // 장비착 후 방어력 증가
	void	SetMinusAttack(int _iAttack); // 장비해제 후 공격력 감소
	void	SetMinusDefence(int _iDefence); // 장비해제 후 방어력 감소
	void	SetPlusHP(int _iHP)	;		//장비 착용후 HP 증가(회복아님)
	void	SetMinusHP(int _iHP);		//장비 해제후 HP감소
	void	SetRecoveryHP(int _iHP);	// 물약 먹었을 때 HP 회복
	

public:
	CPlayer(void);
	~CPlayer(void);
};
