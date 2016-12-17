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
	void	SetDestroy(bool	_YN);			// 외부에서 데스트로이 해줘야될경우
	void	SetBridge(CBridge* pBridge);	// 브릿지 셋해주는함수
	void	SetSelect(bool YN);				// 군중매니저에 선택됬는지 셋
	void	SetTargetPoint(D3DXVECTOR3 pTargetPoint);	// 목표 지점 좌표 셋
	void	SetRevolution(float fAngle);				// 중점기준 공전좌표
	void	SetOrder(ORDERID eOrder);					// 이동명령 타입셋


public:
	CBridge*			GetBridge(void);	// 브릿지 반환
	const bool			GetDestroy(void);	// 파괴해야 될 객체인지 확인
	const INFO*			GetInfo(void) const;// 인포 반환
	const UNITDATA*		GetPlayerStat(void) const; // 플레이어 스텟 반환
	const wstring&		GetObjKey(void);	// ObjKey반환
	const D3DXVECTOR3	GetScroll(void);	// 스크롤값 반환
	const D3DXVECTOR3	GetTargetPoint(void);
	const bool			GetSelect(void);	// 군중 매니저에 선택여부 반환
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
