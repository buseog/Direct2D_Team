// SecondMini.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "SecondMini.h"
#include "BackGround.h"
#include "MainFrm.h"


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
	CBackGround*	pBackGround = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround();

	if (pBackGround == NULL)
		return;

	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	CDevice::GetInstance()->Render_Begin();

	/*if(pBackGround->GetObjCount() < -1)
	{
		pBackGround->SecondRender();
	}*/

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, m_hWnd, NULL);
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
