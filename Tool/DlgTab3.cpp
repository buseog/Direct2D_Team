// DlgTab3.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab3.h"


// CDlgTab3 ��ȭ �����Դϴ�.

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


// CDlgTab3 �޽��� ó�����Դϴ�.

BOOL CDlgTab3::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CRect rect;
   GetClientRect(rect);
   pDC->FillSolidRect( rect, RGB(255,255,255) );

   return TRUE;
}
