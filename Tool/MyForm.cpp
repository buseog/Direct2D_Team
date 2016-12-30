// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
#include "BackGround.h"
#include "MainFrm.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
:CFormView(CMyForm::IDD)
, m_TileY(0)
, m_TileX(0)
{

}

CMyForm::~CMyForm()
{

}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);

	DDX_Text(pDX, IDC_EDIT7, m_TileY);
	DDX_Text(pDX, IDC_EDIT1, m_TileX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnClickButton)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnPathFind)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm::OnItemTool)
END_MESSAGE_MAP()


// CMyForm �����Դϴ�.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm �޽��� ó�����Դϴ�.

/*void CMyForm::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	::Safe_Delete(m_pMapTool);
	::Safe_Delete(m_pUnitTool);
}*/

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_TabCtrl.DeleteAllItems();
	m_TabCtrl.InsertItem(0, L"Map");
	m_TabCtrl.InsertItem(1, L"Object");
	m_TabCtrl.InsertItem(2, L"Monster");

	CRect rect;
	m_TabCtrl.GetClientRect(&rect);

	m_DlgTab1.Create(IDD_DIALOG1, &m_TabCtrl );
	m_DlgTab1.GetWindowRect(&rect);
	m_DlgTab1.MoveWindow(5,25, rect.Width(), rect.Height());
	m_DlgTab1.ShowWindow(SW_SHOW);

	m_DlgTab2.Create(IDD_DIALOG2, &m_TabCtrl );
	m_DlgTab2.GetWindowRect(&rect);
	m_DlgTab2.MoveWindow(5,25, rect.Width(), rect.Height());
	m_DlgTab2.ShowWindow(SW_HIDE);

	m_DlgTab3.Create(IDD_DIALOG3, &m_TabCtrl );
	m_DlgTab3.GetWindowRect(&rect);
	m_DlgTab3.MoveWindow(5,25, rect.Width(), rect.Height());
	m_DlgTab3.ShowWindow(SW_HIDE);

	Invalidate(false);

}

void CMyForm::OnClickButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	m_pBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround();

	m_pBack->SetTile(m_TileX, m_TileY);
	m_pBack->Release();
	m_pBack->Initialize();

	((CMainFrame*)AfxGetMainWnd())->GetMainView()->SetScrollSizes(MM_TEXT, CSize(TILECX * (int)m_TileX, (TILECY / 2) * (int)m_TileY));
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->Invalidate(false);


	UpdateData(FALSE);

}

void CMyForm::OnPathFind()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_PathFind.GetSafeHwnd() == NULL)
	{
		m_PathFind.Create(IDD_PATHFIND);
	}

	m_PathFind.ShowWindow(SW_SHOW);
}

void CMyForm::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	int iIndex = m_TabCtrl.GetCurSel();

	switch(iIndex)
	{
	case 0:
		m_DlgTab1.ShowWindow(SW_SHOW);
		m_DlgTab2.ShowWindow(SW_HIDE);
		m_DlgTab3.ShowWindow(SW_HIDE);
		break;

	case 1:
		m_DlgTab1.ShowWindow(SW_HIDE);
		m_DlgTab2.ShowWindow(SW_SHOW);
		m_DlgTab3.ShowWindow(SW_HIDE);
		break;

	case 2:
		m_DlgTab1.ShowWindow(SW_HIDE);
		m_DlgTab2.ShowWindow(SW_HIDE);
		m_DlgTab3.ShowWindow(SW_SHOW);
		break;
		
	}

	UpdateData(FALSE);

}


CItemTool* CMyForm::GetItemTool(void)
{
	return &m_ItemTool;
}

void CMyForm::OnUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_UnitTool.GetSafeHwnd() == NULL)
	{
		m_UnitTool.Create(IDD_UNITTOOL);
	}

	m_UnitTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnItemTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		if(((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->GetSafeHwnd() == NULL)
	{
		((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->Create(IDD_ITEMTOOL);
	}

	((CMainFrame*)AfxGetMainWnd())->GetForm()->GetItemTool()->ShowWindow(SW_SHOW);
}
