// SecondForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "SecondForm.h"
#include "BackGround.h"
#include "MainFrm.h"


// CSecondForm

IMPLEMENT_DYNCREATE(CSecondForm, CFormView)

CSecondForm::CSecondForm()
	: CFormView(CSecondForm::IDD)
	, m_StateKey(_T(""))
	, m_ObjKey(_T(""))
	, m_PositionX(0)
	, m_PositionY(0)
	, m_PositionZ(0)
	, m_TransX(1)
	, m_TransY(1)
	, m_TransZ(1)
	, m_RotX(0)
	, m_RotY(0)
	, m_RotZ(0)
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
	DDX_Text(pDX, IDC_EDIT4, m_PositionX);
	DDX_Text(pDX, IDC_EDIT12, m_PositionY);
	DDX_Text(pDX, IDC_EDIT13, m_PositionZ);
	DDX_Text(pDX, IDC_EDIT17, m_TransX);
	DDX_Text(pDX, IDC_EDIT18, m_TransY);
	DDX_Text(pDX, IDC_EDIT19, m_TransZ);
	DDX_Text(pDX, IDC_EDIT14, m_RotX);
	DDX_Text(pDX, IDC_EDIT15, m_RotY);
	DDX_Text(pDX, IDC_EDIT16, m_RotZ);
	DDX_Control(pDX, IDC_EDIT4, m_CPositionX);
}

BEGIN_MESSAGE_MAP(CSecondForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CSecondForm::OnLoadButton)
	ON_BN_CLICKED(IDC_BUTTON9, &CSecondForm::OnSaveButton)
	ON_EN_CHANGE(IDC_EDIT4, &CSecondForm::OnPositionChange)
	ON_BN_CLICKED(IDC_BUTTON1, &CSecondForm::OnCreateButton)
	ON_WM_MOUSEMOVE()
	ON_EN_CHANGE(IDC_EDIT12, &CSecondForm::OnEnChangeEdit12)
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

void CSecondForm::Release(void)
{
	/*for_each(m_MapObjectData.begin(), m_MapObjectData.end(), DeleteMap());
	m_MapObjectData.clear();*/
}

void CSecondForm::OnLoadButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // 파일의 확장자명
		L"*.dat", // 최초에 띄워줄 파일 이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
		this);

	if(Dlg.DoModal() == IDCANCEL)
		return;
	
	DWORD	dwByte = 0;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"

	vector<TILE*>*	pvecTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround()->GetTile();
	pvecTile->clear();


	HANDLE	hFile1  = CreateFile(Dlg.GetPathName(), 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		TILE*			pTileData = new TILE;
		ReadFile(hFile1, pTileData, sizeof(TILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			::Safe_Delete(pTileData);
			break;
		}
		pvecTile->push_back(pTileData);
	}


	CloseHandle(hFile1);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

	CFileDialog		Dlg2(TRUE,	// false - save, true - load
		L"dat", // 파일의 확장자명
		L"*.dat", // 최초에 띄워줄 파일 이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
		this);

	if(Dlg2.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath2[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath2), szDirPath2);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath2);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath2);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath2, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"

	HANDLE	hFile2  = CreateFile(Dlg2.GetPathName(), 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	
	vector<BACK*>*	pvecBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround()->GetObject();
	pvecBack->clear();

	Dlg2.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte2 = 0;


	while(true)
	{
		BACK*			pBackData = new BACK;
		ReadFile(hFile2, pBackData, sizeof(BACK), &dwByte2, NULL);

		if(dwByte2 == 0)
		{
			::Safe_Delete(pBackData);
			break;
		}
		pvecBack->push_back(pBackData);
	}

	CloseHandle(hFile2);


	UpdateData(FALSE);

}

void CSecondForm::OnSaveButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
						L"dat", // 파일의 확장자명
						L"*.dat", // 최초에 띄워줄 파일 이름
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
						this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"

	Dlg.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte = 0;

	HANDLE	hFile1  = CreateFile(Dlg.GetPathName(), 
								GENERIC_WRITE, 
								0, 
								NULL, 
								CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL);

	vector<TILE*>*	pvecTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround()->GetTile();

	for(vector<TILE*>::iterator	iter = pvecTile->begin();
		iter != pvecTile->end(); ++iter)
	{
		WriteFile(hFile1, (*iter), sizeof(TILE), &dwByte, NULL);

	}

	CloseHandle(hFile1);

////////////////////////////////////////////////////////////////////////////////////////////////

	CFileDialog		Dlg2(FALSE,	// false - save, true - load
						L"dat", // 파일의 확장자명
						L"*.dat", // 최초에 띄워줄 파일 이름
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
						this);

	if(Dlg2.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath2[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath2), szDirPath2);	// vcproj 파일 위치를 얻어 옴
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath2);	// 응용 프로그램의 현재 작업 디렉토리를 지정된 디렉토리로 바꿔주는 함수
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath2);	// 파일 이름만 남기고 마지막 경로를 삭제
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	lstrcat(szDirPath2, L"\\Data");
	//szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\Data"

	Dlg2.m_ofn.lpstrInitialDir = szDirPath2;	

	DWORD	dwByte2 = 0;


	HANDLE	hFile2  = CreateFile(Dlg2.GetPathName(), 
								GENERIC_WRITE, 
								0, 
								NULL, 
								CREATE_ALWAYS, 
								FILE_ATTRIBUTE_NORMAL, 
								NULL);
	
	vector<BACK*>*	pvecBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround()->GetObject();

	for(vector<BACK*>::iterator	iter = pvecBack->begin();
		iter != pvecBack->end(); ++iter)
	{
		BACK2*	pBack = new BACK2;

		pBack->iIndex = (*iter)->iIndex;
		pBack->vPos = (*iter)->vPos;

		WriteFile(hFile2, pBack, sizeof(BACK2), &dwByte2, NULL);
	}

	CloseHandle(hFile2);

}

void CSecondForm::SetTile(vector<TILE*> _pTile)
{
	m_pTile = _pTile;
}


void CSecondForm::OnPositionChange()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CSecondForm::OnCreateButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	m_pBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetBackGround();

	m_pBack->SetTrans(m_TransX, m_TransY);

	UpdateData(FALSE);
}

void CSecondForm::SetPos(float _fPosx, float _fPosy)
{
	UpdateData(TRUE);

	m_PositionX = _fPosx;
	m_PositionY = _fPosy;
	

//	m_CPositionX.SetDlgItemTextW()

	

	
	UpdateData(FALSE);
	Invalidate(false);
}
void CSecondForm::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFormView::OnMouseMove(nFlags, point);

	Invalidate(false);
}

void CSecondForm::OnEnChangeEdit12()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
