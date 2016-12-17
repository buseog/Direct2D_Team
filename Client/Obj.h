#pragma once

#include "Bigheader.h"

class CBridge;
class CObj
{
protected:
	static  D3DXVECTOR3		m_vScroll;
	D3DXVECTOR3				m_vTargetPoint;
	CBridge*				m_pBridge;

	FRAME					m_tFrame;
	INFO					m_tInfo;
	UNITDATA				m_tUnitData;
	
	int						m_iOrder;
	bool					m_bSelect;
	bool					m_bDestroy;
	float					m_fScrollSpeed;	
	float					m_fRotation;
	float					m_fRevolution;
	wstring					m_wstrObjKey;	

public:
	void	SetPos(const D3DXVECTOR3& vPos);
	void	SetPos(float fX, float fY);		
	void	SetDestroy(bool	_YN);			// �ܺο��� ����Ʈ���� ����ߵɰ��
	void	SetBridge(CBridge* pBridge);	// �긴�� �����ִ��Լ�
	void	SetSelect(bool YN);				// ���߸Ŵ����� ���É���� ��
	void	SetTargetPoint(D3DXVECTOR3 pTargetPoint);	// ��ǥ ���� ��ǥ ��
	void	SetRevolution(float fAngle);				// �������� ������ǥ
	void	SetOrder(ORDERID eOrder);					// �̵���� Ÿ�Լ�


public:
	CBridge*			GetBridge(void);	// �긴�� ��ȯ
	const bool			GetDestroy(void);	// �ı��ؾ� �� ��ü���� Ȯ��
	const INFO*			GetInfo(void) const;// ���� ��ȯ
	const UNITDATA*		GetPlayerStat(void) const; // �÷��̾� ���� ��ȯ
	const wstring&		GetObjKey(void);	// ObjKey��ȯ
	const D3DXVECTOR3	GetScroll(void);	// ��ũ�Ѱ� ��ȯ
	const D3DXVECTOR3	GetTargetPoint(void);
	const bool			GetSelect(void);	// ���� �Ŵ����� ���ÿ��� ��ȯ
	const float			GetRevolution(void);
	const int			GetOrder(void);
	const RECT			GetRect(void);

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
