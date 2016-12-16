#pragma once
#include "objbridge.h"

class CBackBridge :
	public CObjBridge
{
protected:
	vector<TILE2*>		m_vecTile;

protected:
	void	LoadTile(const wstring& wstrPath);

public:
	const vector<TILE2*>* GetTile(void);	
public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CBackBridge(void);
	virtual ~CBackBridge(void);
};
