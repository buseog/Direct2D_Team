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

	void	SetStat(int _iIndex);	// �÷��̾� ���� 
	void	SetPlusAttack(int _iAttack); // ��������� ���ݷ� ����
	void	SetPlusDefence(int _iDefence); // ��������� ���� ����
	void	SetMinusAttack(int _iAttack); // ��������� ���ݷ� ����
	void	SetMinusDefence(int _iDefence); // ��������� ���� ����


public:
	CPlayer(void);
	~CPlayer(void);
};
