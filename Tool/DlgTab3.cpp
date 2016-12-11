// DlgTab3.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab3.h"


// CDlgTab3 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTab3, CDialog)

CDlgTab3::CDlgTab3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTab3::IDD, pParent)
{

}

CDlgTab3::~CDlgTab3()
{
}

void CDlgTab3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTab3, CDialog)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDlgTab3 메시지 처리기입니다.

BOOL CDlgTab3::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
   GetClientRect(rect);
   pDC->FillSolidRect( rect, RGB(255,255,255) );

   return TRUE;
}
