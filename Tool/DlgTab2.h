#pragma once
#include "afxwin.h"
#include "SecondForm.h"
#include "BackGround.h"


// CDlgTab2 ��ȭ �����Դϴ�.

class CDlgTab2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTab2();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();

public: 
	CListBox m_ListBox02;
	CSecondForm*		m_pSecondForm;
	CBackGround*		m_pBack;
	
public:
	afx_msg void OnAddBox();
	void	ListBoxAddItem(void);
	CString			m_szStateKey;
	CString			m_szObjKey;
	int				m_iCount;
	
};
