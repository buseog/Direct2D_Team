#pragma once
#include "uibridge.h"

class CItem;
class CInvenBridge :
	public CUiBridge
{

protected:
	virtual void	WorldMatrix(INFO& rInfo);

private:
	vector<CItem*>	m_ItemSlot;
	vector<CItem*>	m_EquipSlot;
	vector<CItem*>	m_TempSlot;
	

private:
	INFO	m_tInfo;
	int		m_iSelectIndex;
	int		m_iFood;
	bool	m_bSelect;
	bool	m_bDrag;
	bool	m_bWeapon;
	bool	m_bArmor;	


public:
	void SortItem(INFO& rInfo);
	void AddItem(INFO& rInfo);
	void SetItem(INFO& rInfo);
	int Picking(INFO& rInfo);
	CItem*	CreateWeapon(D3DXVECTOR3 vPos);
	CItem*	CreateArmor(D3DXVECTOR3 vPos);
	CItem*	CreateFood(D3DXVECTOR3 vPos);
	CItem*	CreateEmpty(D3DXVECTOR3 vPos);
	
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

	virtual int		Picking(void);


public:
	CInvenBridge(void);
	virtual ~CInvenBridge(void);
};
