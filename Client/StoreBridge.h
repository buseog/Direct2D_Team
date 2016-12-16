#pragma once
#include "uibridge.h"

class CItem;
class CStoreBridge :
	public CUiBridge
{

protected:
	virtual void	WorldMatrix(INFO& rInfo);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(void);

private:
	BOOL m_bState;
	BOOL m_bToolTip;
	unsigned int m_iToolTipIndex;
	vector<CItem*> m_vecItem;
	vector<ITEM*> m_vecLoadItemData;
	const TEXINFO* pTexture;
	const TEXINFO*  pItemTexture;
	const TEXINFO*  pToolTipTexture;
private:
	void AddItem(ITEMID _itemid,int _iIndex);
	void DeleteContainedOverItem(void);
	void ShowToolTip(/*int _iIndex,*/);
	void LoadData(void);
public :
	void SetState(void);
	
public:
	CStoreBridge(void);
	~CStoreBridge(void);
};
