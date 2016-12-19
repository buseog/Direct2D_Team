#pragma once
#include "uibridge.h"

class CItem;
class CUnit;
class CStoreBridge :
	public CUiBridge
{

protected:
	virtual void	WorldMatrix(INFO& rInfo);

protected:
	vector<CItem*>	m_ItemSlot;
	vector<CUnit*>  m_UnitSlot;
	vector<CItem*>	m_TempSlot;
	

protected:
	INFO	m_tInfo;
	int		m_iSelectIndex;
	int		m_iFood;
	bool	m_bSelect;
	bool	m_bTooltip;
	bool	m_bPick;
	bool	m_bMove;	


public:
	virtual void SortItem(INFO& rInfo);
	virtual void AddItem(INFO& rInfo);
	virtual void LoadData(void);
	virtual void ShowTooltip(void);
	virtual void BuyItem(void);
	//virtual void SetItem(INFO& rInfo);
	
	CItem*	CreateWeapon(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateArmor(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateGlove(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateHelmet(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateBoots(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateBelt(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateFood(ITEM* _pItem,D3DXVECTOR3 vPos);
	CItem*	CreateEmpty(D3DXVECTOR3 vPos);

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
	CStoreBridge(void);
	virtual ~CStoreBridge(void);
};
