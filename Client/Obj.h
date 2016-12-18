#pragma once

#include "Bigheader.h"
#include "Bridge.h"

class CObj
{
protected:
	static  D3DXVECTOR3		m_vScroll;
	D3DXVECTOR3				m_vTargetPoint;
	D3DXVECTOR3				m_vOriginPos;
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
	wstring					m_wstrStateKey;

private:
	bool		m_bHit;

public:
	void	SetPos(const D3DXVECTOR3& vPos);
	void	SetPos(float fX, float fY);		
	void	SetDestroy(bool	_YN);			// 외부에서 데스트로이 해줘야될경우
	void	SetBridge(CBridge* pBridge);	// 브릿지 셋해주는함수
	void	SetSelect(bool YN);				// 군중매니저에 선택됬는지 셋
	void	SetRevolution(float fAngle);				// 중점기준 공전좌표
	void	SetOrder(ORDERID eOrder);					// 이동명령 타입셋
	void	SetScroll(float fX, float fY);				// 스크롤 셋해주는함수
	void	SetSize(D3DXVECTOR3 vSize);					// 렉트 충돌하기위한 사이즈 지정함수
	void	SetSpeed(float fSpeed);
	void	SetObjKey(const wstring& wstrObjKey);
	void	SetHit(bool bHit);
	void	SetTargetPoint(D3DXVECTOR3 pTargetPoint);	// 이동 목표 지점 좌표 셋
	void	SetOriginPos(D3DXVECTOR3 OriginPos);		// 패트롤용 본래 좌표지정
	void	SetDamage(int iAttack);						// 충돌처리 대미지 셋


public:
	int					Picking(void);
	CBridge*			GetBridge(void);	// 브릿지 반환
	const INFO*			GetInfo(void) const;// 인포 반환
	const UNITDATA*		GetStat(void) const; // 유닛 스텟 반환
	const wstring&		GetObjKey(void);		// ObjKey반환
	const wstring&		GetStateKey(void);		// ObjKey반환
	const bool			GetDestroy(void);	// 파괴해야 될 객체인지 확인
	const bool			GetSelect(void);		// 군중 매니저에 선택여부 반환
	const float			GetRevolution(void);	// 공전(목표 주변으로의 각도) 각도를 반환해줌
	const float			GetSpeed(void);			// 스피드값 반환
	const int			GetOrder(void);			// 오더상태를 반환함(0// 스탠드, 1//에이스타, 2// 무브)
	const RECT			GetRect(void);			// 렉트 사이즈 반환 충돌용.
	bool				GetHit(void);
	const D3DXVECTOR3	GetOriginPos(void);
	const D3DXVECTOR3	GetScroll(void);		// 스크롤값 반환
	const D3DXVECTOR3	GetTargetPoint(void);	// 목표지점을 반환해줌

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual void	Progress(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
