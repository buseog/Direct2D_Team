#pragma once
#include "obj.h"

class CBack :
	public CObj
{
private:
	vector<TILE2*>		m_vecTile;
	int					m_iTileRenderX;
	int					m_iTileRenderY;
	int					m_iDragState;
	RECT				m_rcDrag;
	D3DXVECTOR2			m_vDrag[5];

private:
	void	LoadTile(const wstring& wstrPath);
	void	MoveScroll(void);
	void	MouseLock(void);
	void	Drag(void);

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
