#pragma once
#include "objbridge.h"

class CBackBridge :
	public CObjBridge
{
protected:
	int					m_iX;
	int					m_iY;
	D3DXVECTOR3			m_vSize;
	vector<TILE2*>		m_vecTile;
	vector<BACK*>		m_vecBack;

protected:
	void	LoadTile(const wstring& wstrPath);
	void	LoadBack(const wstring&	wstrPath);

public:
	const vector<TILE2*>* GetTile(void);
	const D3DXVECTOR3*		GetSize(void);

public:
	virtual HRESULT	Initialize(void);
	virtual void	Progress(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);
	virtual int		Picking(void);

public:
	CBackBridge(void);
	virtual ~CBackBridge(void);
};
