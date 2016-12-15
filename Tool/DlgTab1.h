#pragma once
#include "afxwin.h"
#include "SecondForm.h"
#include "BackGround.h"


// CDlgTab1 대화 상자입니다.

class CDlgTab1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgTab1();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();

public: // 기본 함수
	CListBox m_ListBox01;
	CSecondForm*	m_pSecondForm;
	CBackGround*	m_pBack;

public: // 리스트 박스 클릭 관련 기능
	afx_msg void OnAddBox();
	int				m_iCount;
};
