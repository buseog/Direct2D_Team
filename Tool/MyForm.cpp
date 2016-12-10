// MyForm.cpp : 구현 파일입니다.
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


// CMyForm 진단입니다.

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


// CMyForm 메시지 처리기입니다.

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	m_ToolComboList.AddString(L"Map Tool");
	m_ToolComboList.AddString(L"Unit Tool");
	m_ToolComboList.AddString(L"Item Tool");
	m_ToolComboList.AddString(L"Village Tool");

	m_ToolComboList.SetCurSel(0);
}

void CMyForm::OnToolComboBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

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