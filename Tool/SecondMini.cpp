// SecondMini.cpp : 구현 파일입니다.
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


// CSecondMini 그리기입니다.

void CSecondMini::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CSecondMini 진단입니다.

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


// CSecondMini 메시지 처리기입니다.
