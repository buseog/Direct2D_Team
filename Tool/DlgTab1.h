#pragma once


// CDlgTab1 ��ȭ �����Դϴ�.

class CDlgTab1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTab1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int m_ListBox1;
	virtual BOOL OnInitDialog();
};
