#pragma once
#include "afxwin.h"


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

public:
	void	ListBoxAddItem(void);
	virtual BOOL OnInitDialog();

	CListBox m_ListBox02;
};
