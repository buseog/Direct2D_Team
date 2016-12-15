#pragma once
#include "afxwin.h"
#include "SecondForm.h"
#include "BackGround.h"


// CDlgTab2 대화 상자입니다.

class CDlgTab2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTab2();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
