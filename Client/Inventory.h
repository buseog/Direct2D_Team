#pragma once
#include "ui.h"

class CItem;
class CInventory :
	public CUi
{
private:
	vector<CItem*>	m_ItemSlot;

public:
	void AddItem();
	void Picking();
	CItem*	CreateItem(float _fX, float _fY,float _fCX, float _fCY, string _strITname);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CInventory(void);
	virtual ~CInventory(void);
};
