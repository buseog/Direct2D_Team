// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
:CFormView(CMyForm::IDD)
,m_pMapTool(NULL)
,m_pUnitTool(NULL)
,m_pItemTool(NULL)
,m_pVillageTool(NULL)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_ToolComboList);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyForm::OnToolComboBox)
	ON_WM_DESTROY()
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

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_ToolComboList.AddString(L"Map Tool");
	m_ToolComboList.AddString(L"Unit Tool");
	m_ToolComboList.AddString(L"Item Tool");
	m_ToolComboList.AddString(L"Village Tool");

	m_ToolComboList.SetCurSel(0);
}

void CMyForm::OnToolComboBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	switch (m_ToolComboList.GetCurSel())
	{
	case 0:
		if (m_pMapTool == NULL)
		{
			m_pMapTool = new CMapTool;
			m_pMapTool->Create(IDD_MAPTOOL);
		}

		m_pMapTool->ShowWindow(SW_SHOW);
		break;

	case 1:
		if (m_pUnitTool == NULL)
		{
			m_pUnitTool = new CUnitTool;
			m_pUnitTool->Create(IDD_UNITTOOL);
		}

		m_pUnitTool->ShowWindow(SW_SHOW);
		break;

	case 2:
		if (m_pItemTool == NULL)
		{
			m_pItemTool = new CItemTool;
			m_pItemTool->Create(IDD_ITEMTOOL);
		}

		m_pItemTool->ShowWindow(SW_SHOW);
		break;

	case 3:
		if (m_pVillageTool == NULL)
		{
			m_pVillageTool = new CVillageTool;
			m_pVillageTool->Create(IDD_VILLAGETOOL);
		}

		m_pVillageTool->ShowWindow(SW_SHOW);
		break;
	}
}

void CMyForm::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	::Safe_Delete(m_pMapTool);
	::Safe_Delete(m_pUnitTool);
	::Safe_Delete(m_pVillageTool);
}

CMapTool*	CMyForm::GetMapTool(void)
{
	return m_pMapTool;
}

CUnitTool*	CMyForm::GetUnitTool(void)
{
	return m_pUnitTool;
}