// DlgTab2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab2.h"
#include "MainFrm.h"


// CDlgTab2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgTab2, CDialog)

CDlgTab2::CDlgTab2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTab2::IDD, pParent)
{

}

CDlgTab2::~CDlgTab2()
{
}

void CDlgTab2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBox02);
}


BEGIN_MESSAGE_MAP(CDlgTab2, CDialog)
	ON_WM_ERASEBKGND()
	ON_LBN_SELCHANGE(IDC_LIST2, &CDlgTab2::OnAddBox)
END_MESSAGE_MAP()


// CDlgTab2 메시지 처리기입니다.

BOOL CDlgTab2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
   GetClientRect(rect);
   pDC->FillSolidRect( rect, RGB(255,255,255) );

   return TRUE;
}

void CDlgTab2::ListBoxAddItem(void)
{

}

BOOL CDlgTab2::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	UpdateData(TRUE);

	wifstream		LoadFile;
	LoadFile.open("../Data/ObjPath.txt", ios::in);

	TCHAR		szImgPath[MAX_PATH] = L"";

	wstring		wstrCombine = L"";
	m_ListBox02.ResetContent();

	while(!LoadFile.eof())
	{
		LoadFile.getline(szImgPath, MAX_PATH);
		
		wstrCombine = wstring(szImgPath);

		m_ListBox02.AddString(wstrCombine.c_str());
	}

	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDlgTab2::OnAddBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	m_iCount = m_ListBox02.GetCurSel();

	m_pBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround();

	m_pBack->SetObjCount(m_iCount);
	m_pBack->SetObjszObj(L"OBJECT");
	m_pBack->SetObjszState(L"Object");

	Invalidate(false);
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->Invalidate(false);
	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->Invalidate(false);

	UpdateData(FALSE);

}
