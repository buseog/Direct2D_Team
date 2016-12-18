#pragma once
#include "uibridge.h"

class CItem;
class CUnit;
class CMercenaryDisplayBridge :
	public CUiBridge
{

protected:
	virtual void	WorldMatrix(INFO& rInfo);

protected:
	//vector<CItem*>	m_ItemSlot;
	vector<CUnit*>  m_UnitSlot;
	vector<CItem*>	m_TempSlot;
//	vector<CUnit*>  m_UnitSlot;
	

protected:
	INFO	m_tInfo;
	int		m_iSelectIndex;
	int		m_iFood;
	bool	m_bSelect;
	bool	m_bDrag;
	bool	m_bWeapon;
	bool	m_bArmor;	


public:
	virtual void SortItem(INFO& rInfo);
	virtual void AddItem(INFO& rInfo);
	virtual void LoadData(void);
	//virtual void SetItem(INFO& rInfo);
	
	CUnit* CreateUnitAlly(UNITDATA* _pUnit,D3DXVECTOR3 vPos);
	CUnit* CreateUnitEnemy(UNITDATA* _pUnit,D3DXVECTOR3 vPos);
	CUnit*	CreateEmptyUnit(D3DXVECTOR3 vPos);
	
	
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(void);


public:
	CMercenaryDisplayBridge(void);
	virtual ~CMercenaryDisplayBridge(void);
};
