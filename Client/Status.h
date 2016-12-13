#pragma once
#include "ui.h"

//class CItem;
class CStatus :
	public CUi
{
public:
	void AddItem();
	void Picking();
	//CItem*	CreateItem(float _fX, float _fY,float _fCX, float _fCY, string _strITname);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);


public:
	CStatus(void);
	virtual ~CStatus(void);
};
