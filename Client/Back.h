#pragma once
#include "obj.h"

class CBack :
	public CObj
{
private:
	vector<TILE2*>		m_vecTile;
	int					m_iTileRenderX;
	int					m_iTileRenderY;

public:
	const vector<TILE2*>* GetTile(void);

private:
	void LoadTile(const wstring& wstrPath);

public:
	virtual HRESULT Initialize(void);
	virtual void Progress(void);
	virtual void Render(void);
	virtual void Release(void);

public:
	CBack(void);
	~CBack(void);
};
