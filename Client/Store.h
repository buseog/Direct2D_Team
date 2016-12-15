#pragma once
#include "ui.h"

class CItem;
class CStore :
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
	CStore(void);
	virtual ~CStore(void);
};
