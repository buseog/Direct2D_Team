// SecondMini.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SecondMini.h"


// CSecondMini

IMPLEMENT_DYNCREATE(CSecondMini, CView)

CSecondMini::CSecondMini()
{

}

CSecondMini::~CSecondMini()
{
}

BEGIN_MESSAGE_MAP(CSecondMini, CView)
END_MESSAGE_MAP()


// CSecondMini �׸����Դϴ�.

void CSecondMini::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
}


// CSecondMini �����Դϴ�.

#ifdef _DEBUG
void CSecondMini::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondMini::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSecondMini �޽��� ó�����Դϴ�.
