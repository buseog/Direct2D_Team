#pragma once

class CItem
{
public:
	CItem(void);
	virtual ~CItem(void);

protected:
	ITEM					m_tItem;
	INFO					m_tInfo;
	wstring					m_wstrObjKey;

public:
	wstring GetItemKey(void);
	ITEM*	GetItemInfo(void);
	INFO*	GetInfo(void);
	void	SetItemProperty(wstring _Name, ITEMID _eType,int _iOption,int _iPrice, int _iWeight);
	void SetPos(D3DXVECTOR3 _vPos);
};
