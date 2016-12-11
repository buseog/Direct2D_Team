// DlgTab1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab1.h"


// CDlgTab1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTab1, CDialog)

CDlgTab1::CDlgTab1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTab1::IDD, pParent)
	, m_ListBox1(0)
{
}

CDlgTab1::~CDlgTab1()
{
}

void CDlgTab1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTab1, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgTab1 메시지 처리기입니다.

BOOL CDlgTab1::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
   GetClientRect(rect);
   pDC->FillSolidRect( rect, RGB(255,255,255) );

   return TRUE;
}

BOOL CDlgTab1::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
