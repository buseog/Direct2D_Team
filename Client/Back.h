#pragma once
#include "obj.h"

class CBack :
	public CObj
{
private:
	void	MoveScroll(void);
	void	MouseLock(void);


public:
	const vector<TILE2*>* GetTile(void);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CBack(void);
	~CBack(void);
};
