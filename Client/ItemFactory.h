#pragma once

#include "Item.h"

template <typename T>
class CItemFactory
{
public:
	static CItem*	CreateItem(void)
	{
		CItem*	pItem = new T;
		pItem->Initialize();
	
		return pItem;
	}
	
	static CItem* CreateItem(float _fX, float _fY)
	{
		CItem*		pItem = new T;
		pItem->Initialize();
		pItem->SetPos(_fX, _fY);
	
		return pItem;
	}



	static CItem* CreateItem(D3DXVECTOR3 vPos)	
	{
		CItem*		pItem = new T;
		pItem->Initialize();
		pItem->SetPos(vPos);
		return pItem;
	}


public:
	CItemFactory(void){ }
	~CItemFactory(void){ }
};
