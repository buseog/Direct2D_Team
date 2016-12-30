
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
#include "Tool.h"

#include "ToolDoc.h"
#include "ToolView.h"

#include "Bigheader.h"
#include "TextureMgr.h"
#include "MainFrm.h"
#include "KeyMgr.h"
#include "BackGround.h"
#include "SecondForm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND	g_hWnd;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CToolView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_ACTIVATE()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
: m_pBack(NULL)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	CDevice::GetInstance()->Render_Begin();

	m_pBack->Render();

	

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
}


// CToolView �μ�


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CToolView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CToolView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY / 2) * TILEY));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

	RECT		rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);		// ��ü �����ӿ� ���� ����� ���ͼ� ��Ʈ�� ����


	SetRect(&rcWindow, 0, 0, 
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top);

	RECT		rcMainView;
	GetClientRect(&rcMainView);		// ���� �� â�� ũ�⸦ ������ �Լ�

	float		fRowFrm = float(rcWindow.right - rcMainView.right);		// ���� �÷��� ����
	float		fColFrm = float(rcWindow.bottom - rcMainView.bottom);	// ���� �÷��� ����

	pMainFrm->SetWindowPos(NULL,	// ������ ũ����� ���Ͽ� â�� ��ġ�� �������ϴ� �Լ�
		400, 100, 
		int(WINCX + 440),  // ���� ���� 
		int(WINCY + fColFrm), 
		SWP_NOZORDER);

	g_hWnd = m_hWnd;

	if(FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"����̽� ��ġ �ʱ�ȭ ����");
		return;
	}

	/*if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Cube.png", 
		L"CUBE", TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �ؽ��� ���� ����");
		return;
	}*/

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map0%d.png", //  �� �ؽ��� - ���� �߰�
		L"MAP", TEX_MULTI, L"Map", 3)))
	{
		AfxMessageBox(L"�� �ؽ��� ���� ����");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/TILEMAP/TILE0%d.png",  // Ÿ�� �ؽ��� - ���� �߰�
		L"TILE", TEX_MULTI, L"Tile", 4)))
	{
		AfxMessageBox(L"Ÿ�� �ؽ��� ���� ����");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Back/Object2/Back00%d.png",  // ���� ������Ʈ �ؽ��� - ���� �߰�
		L"OBJECT", TEX_MULTI, L"Object", 55)))
	{
		AfxMessageBox(L"���� ������Ʈ �ؽ��� ���� ����");
		return;
	}


	m_pBack = new CBackGround;

	if(FAILED(m_pBack->Initialize()))
	{
		AfxMessageBox(L"CBackGround ���� ����");
		return;
	}

	m_pBack->SetMainView(this);

	
}

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	::Safe_Delete(m_pBack);
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

CBackGround*	CToolView::GetBackGround(void)
{
	return m_pBack;
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)	// Ÿ�� ��ŷ - ���� �߰�
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CScrollView::OnLButtonDown(nFlags, point);

	D3DXVECTOR3 Mouse = ::GetMouse();

	//Mouse.x += GetScrollPos(0);
	//Mouse.y += GetScrollPos(1);
	
	m_pBack->TileChange(D3DXVECTOR3(
		Mouse.x + GetScrollPos(0) ,
		Mouse.y + GetScrollPos(1), 0.f), 1);
	
 	Invalidate(false);
	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->Invalidate(false);
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{

	CScrollView::OnMouseMove(nFlags, point);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	m_pSecond = ((CMainFrame*)AfxGetMainWnd())->GetSecondForm();


	D3DXVECTOR3 Mouse = ::GetMouse();

	m_pSecond->SetPos(Mouse.x, Mouse.y);


	m_pSecond->Invalidate(false);

	if (CKeyMgr::GetInstance()->KeyDown('P'))
	{
		if (m_pBack->GetTileCheck())
			m_pBack->SetTileCheck(false);
		else
			m_pBack->SetTileCheck(true);
	}
	
	Invalidate(false);

}

void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnRButtonDown(nFlags, point);

		
	D3DXVECTOR3 vMouse = ::GetMouse();

	m_pBack->ObjPick(vMouse, ((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_iCount,
		((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_szObjKey,
		((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_szStateKey);

	Invalidate(false);
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�

	/*if (CKeyMgr::GetInstance()->KeyDown('P'))
	{
		if (m_pBack->GetTileCheck())
			m_pBack->SetTileCheck(false);
		else
			m_pBack->SetTileCheck(true);
	}*/
	
	//Invalidate(false);

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);

}

void CToolView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CScrollView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

}

void CToolView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}
