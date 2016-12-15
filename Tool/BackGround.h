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
	vector<BACK*>		m_vecBack;

public:
	void	TileChange(const D3DXVECTOR3& vPos, const int& iDrawID/*, const int& iSize, const int& iOption, const float& fAngle, const float& fMirror*/);
	int		GetTileIndex(const D3DXVECTOR3&	vPos);
	bool	Picking(const D3DXVECTOR3& vPos, const int& iIndex);
	void	ReturnAction(void);

	vector<TILE*>*	GetTile(void); // ���� �߰� - ���̺� �ε� ����
	vector<BACK*>*	GetObject(void);	// ���� �߰� - ���̺� �ε� ����

public:
	HRESULT		Initialize(void);
	void		Progress(void);
	void		Render(void);
	void		MiniRender(void);
	void		SecondRender(void); // ���� �߰�
	void		Release(void);

public:
	void	SetMainView(CToolView*	pMainView);
	void	SetTile(float _fX, float _fY);

public:	// ��ŷ Ÿ�� ���� - ���� �߰�
	bool		m_bTileCheck;
	void		SetTileCheck(bool _bTileCheck);
	bool		GetTileCheck(void);

public:	// ��׶��� �� ���� - ���� �߰�
	int			m_iCountKey;
	void		SetCount(int _iCountKey);
	
public: // ���� ������Ʈ ���� - ���� �߰�
	int			m_iBackCountKey;
	CString		m_szBackStateKey;
	CString		m_szBackObjKey;
	void		SetObjCount(int _iBackCountKey);
	int			GetObjCount(void);
	void		SetObjszState(CString _szStateKey);
	void		SetObjszObj(CString	_szObjKey);
	void		ObjPick(D3DXVECTOR3& vPos, int& iIndex, CString& szObj, CString& szState);
	void		ObjRender(void);


public:
	CBackGround(void);
	~CBackGround(void);
};
