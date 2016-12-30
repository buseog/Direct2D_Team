#pragma once
#include "afxwin.h"
#include "BackGround.h"


// CSecondForm �� ���Դϴ�.

class CMainFrm;
class CSecondForm : public CFormView
{
	DECLARE_DYNCREATE(CSecondForm)

public:
	CSecondForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CSecondForm();

public:
	enum { IDD = IDD_SECONDFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public: //��ġ ��� ����
	CString m_StateKey;
	CString m_ObjKey;
public: // ���̺�, �ε� ����
	afx_msg void	OnLoadButton();
	afx_msg void	OnSaveButton();
	void			Release(void);	
	void			SetTile(vector<TILE*> _pTile);
	vector<TILE*>	m_pTile;

	/*map<BYTE, TILE*>	m_MapTileData;
	map<int, BACK*>		m_MapObjectData;*/

	CBackGround*	m_pBack;

	afx_msg void OnPositionChange();
	float m_PositionX;
	float m_PositionY;
	float m_PositionZ;
	float m_TransX;
	float m_TransY;
	float m_TransZ;

	afx_msg void OnCreateButton();
	float m_RotX;
	float m_RotY;
	float m_RotZ;

	void	SetPos(float _fPosx, float _fPosy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_CPositionX;
	afx_msg void OnEnChangeEdit12();


};


