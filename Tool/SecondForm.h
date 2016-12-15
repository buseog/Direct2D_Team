#pragma once


// CSecondForm �� ���Դϴ�.

class CSecondForm : public CFormView
{
	DECLARE_DYNCREATE(CSecondForm)

protected:
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

	void	SetKey(float _fObjKey, float _StateKey);

public: // ���̺�, �ε� ����
	afx_msg void	OnLoadButton();
	afx_msg void	OnSaveButton();
	void			Release(void);	
	void			SetTile(vector<TILE*> _pTile);
	vector<TILE*>	m_pTile;

	/*map<BYTE, TILE*>	m_MapTileData;
	map<int, BACK*>		m_MapObjectData;*/

};


