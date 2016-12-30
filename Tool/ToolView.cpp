
// ToolView.cpp : CToolView 클래스의 구현
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
	// 표준 인쇄 명령입니다.
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

// CToolView 생성/소멸

CToolView::CToolView()
: m_pBack(NULL)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CDevice::GetInstance()->GetDevice()->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	CDevice::GetInstance()->Render_Begin();

	m_pBack->Render();

	

	CDevice::GetInstance()->Render_End();
	CDevice::GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
}


// CToolView 인쇄


void CToolView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
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


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기

void CToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY / 2) * TILEY));

	CMainFrame*		pMainFrm = ((CMainFrame*)AfxGetMainWnd());

	RECT		rcWindow;
	pMainFrm->GetWindowRect(&rcWindow);		// 전체 프레임에 대한 사이즈를 얻어와서 렉트에 저장


	SetRect(&rcWindow, 0, 0, 
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top);

	RECT		rcMainView;
	GetClientRect(&rcMainView);		// 순수 뷰 창의 크기를 얻어오는 함수

	float		fRowFrm = float(rcWindow.right - rcMainView.right);		// 가로 플레임 길이
	float		fColFrm = float(rcWindow.bottom - rcMainView.bottom);	// 세로 플레임 길이

	pMainFrm->SetWindowPos(NULL,	// 프레임 크기들을 합하여 창의 위치를 재조정하는 함수
		400, 100, 
		int(WINCX + 440),  // 은지 변경 
		int(WINCY + fColFrm), 
		SWP_NOZORDER);

	g_hWnd = m_hWnd;

	if(FAILED(CDevice::GetInstance()->InitDevice()))
	{
		AfxMessageBox(L"디바이스 장치 초기화 실패");
		return;
	}

	/*if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Cube.png", 
		L"CUBE", TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 텍스쳐 생성 실패");
		return;
	}*/

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Map/Map0%d.png", //  맵 텍스쳐 - 은지 추가
		L"MAP", TEX_MULTI, L"Map", 3)))
	{
		AfxMessageBox(L"맵 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/TILEMAP/TILE0%d.png",  // 타일 텍스쳐 - 은지 추가
		L"TILE", TEX_MULTI, L"Tile", 4)))
	{
		AfxMessageBox(L"타일 텍스쳐 생성 실패");
		return;
	}

	if(FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Back/Object2/Back00%d.png",  // 지형 오브젝트 텍스쳐 - 은지 추가
		L"OBJECT", TEX_MULTI, L"Object", 55)))
	{
		AfxMessageBox(L"지형 오브젝트 텍스쳐 생성 실패");
		return;
	}


	m_pBack = new CBackGround;

	if(FAILED(m_pBack->Initialize()))
	{
		AfxMessageBox(L"CBackGround 생성 실패");
		return;
	}

	m_pBack->SetMainView(this);

	
}

void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	::Safe_Delete(m_pBack);
	CTextureMgr::GetInstance()->DestroyInstance();
	CDevice::GetInstance()->DestroyInstance();
}

CBackGround*	CToolView::GetBackGround(void)
{
	return m_pBack;
}

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)	// 타일 피킹 - 은지 추가
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnRButtonDown(nFlags, point);

		
	D3DXVECTOR3 vMouse = ::GetMouse();

	m_pBack->ObjPick(vMouse, ((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_iCount,
		((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_szObjKey,
		((CMainFrame*)AfxGetMainWnd())->GetForm()->m_DlgTab2.m_szStateKey);

	Invalidate(false);
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

}

void CToolView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnKeyUp(nChar, nRepCnt, nFlags);
}
