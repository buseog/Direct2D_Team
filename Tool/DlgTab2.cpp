// DlgTab2.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "DlgTab2.h"
#include "MainFrm.h"


// CDlgTab2 ��ȭ �����Դϴ�.

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


// CDlgTab2 �޽��� ó�����Դϴ�.

BOOL CDlgTab2::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}



void CDlgTab2::OnAddBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
