#pragma once
#include "afxwin.h"
#include "SecondForm.h"
#include "BackGround.h"


// CDlgTab1 ��ȭ �����Դϴ�.

class CDlgTab1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDlgTab1();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();

public: // �⺻ �Լ�
	CListBox m_ListBox01;
	CSecondForm*	m_pSecondForm;
	CBackGround*	m_pBack;

public: // ����Ʈ �ڽ� Ŭ�� ���� ���
	afx_msg void OnAddBox();
	int				m_iCount;
};
