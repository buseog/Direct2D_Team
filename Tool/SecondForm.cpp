// SecondForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "SecondForm.h"


// CSecondForm

IMPLEMENT_DYNCREATE(CSecondForm, CFormView)

CSecondForm::CSecondForm()
	: CFormView(CSecondForm::IDD)
	, m_StateKey(_T(""))
	, m_ObjKey(_T(""))
{

}

CSecondForm::~CSecondForm()
{
}

void CSecondForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, m_StateKey);
	DDX_Text(pDX, IDC_EDIT8, m_ObjKey);
}

BEGIN_MESSAGE_MAP(CSecondForm, CFormView)
END_MESSAGE_MAP()


// CSecondForm 진단입니다.

#ifdef _DEBUG
void CSecondForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSecondForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSecondForm 메시지 처리기입니다.
