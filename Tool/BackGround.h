#pragma once
#include "Bigheader.h"

class CDevice;
class CToolView;


class CBackGround
{
private:
	vector<TILE*>		m_vecTile;
	CDevice*			m_pDevice;
	CToolView*			m_pMainView;
	vector<TILE_ACTION*>		m_vecAction;

public:
	void	TileChange(const D3DXVECTOR3& vPos, const int& iDrawID, const int& iSize, const int& iOption, const float& fAngle, const float& fMirror);
	int		GetTileIndex(const D3DXVECTOR3&	vPos);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	void	ReturnAction(void);

public:
	HRESULT		Initialize(void);
	void		Progress(void);
	void		Render(void);
	void		MiniRender(void);
	void		Release(void);

public:
	void	SetMainView(CToolView*	pMainView);

public:
	CBackGround(void);
	~CBackGround(void);
};
