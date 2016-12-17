#pragma once

#include "Bigheader.h"
#include "Bridge.h"

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
	float					m_fSpeed;
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
	void	SetScroll(float fX, float fY);				// ��ũ�� �����ִ��Լ�
	void	SetSize(D3DXVECTOR3 vSize);					// ��Ʈ �浹�ϱ����� ������ �����Լ�


public:
	CBridge*			GetBridge(void);	// �긴�� ��ȯ
	const bool			GetDestroy(void);	// �ı��ؾ� �� ��ü���� Ȯ��
	const INFO*			GetInfo(void) const;// ���� ��ȯ
	const UNITDATA*		GetStat(void) const; // ���� ���� ��ȯ
	const wstring&		GetObjKey(void);		// ObjKey��ȯ
	const D3DXVECTOR3	GetScroll(void);		// ��ũ�Ѱ� ��ȯ
	const D3DXVECTOR3	GetTargetPoint(void);	// ��ǥ������ ��ȯ����
	const bool			GetSelect(void);		// ���� �Ŵ����� ���ÿ��� ��ȯ
	const float			GetRevolution(void);	// ����(��ǥ �ֺ������� ����) ������ ��ȯ����
	const int			GetOrder(void);			// �������¸� ��ȯ��(0// ���ĵ�, 1//���̽�Ÿ, 2// ����)
	const RECT			GetRect(void);			// ��Ʈ ������ ��ȯ �浹��.
	const float			GetSpeed(void);			// ���ǵ尪 ��ȯ

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
