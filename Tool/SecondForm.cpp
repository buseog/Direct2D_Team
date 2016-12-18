// SecondForm.cpp : ���� �����Դϴ�.
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
	ON_BN_CLICKED(IDC_BUTTON2, &CSecondForm::OnLoadButton)
	ON_BN_CLICKED(IDC_BUTTON9, &CSecondForm::OnSaveButton)
END_MESSAGE_MAP()


// CSecondForm �����Դϴ�.

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


// CSecondForm �޽��� ó�����Դϴ�.

void CSecondForm::Release(void)
{
	/*for_each(m_MapObjectData.begin(), m_MapObjectData.end(), DeleteMap());
	m_MapObjectData.clear();*/
}

void CSecondForm::OnLoadButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // ������ Ȯ���ڸ�
		L"*.dat", // ���ʿ� ����� ���� �̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
		this);

	if(Dlg.DoModal() == IDCANCEL)
		return;
	
	DWORD	dwByte = 0;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// ���� �̸��� ����� ������ ��θ� ����
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
		L"dat", // ������ Ȯ���ڸ�
		L"*.dat", // ���ʿ� ����� ���� �̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
		this);

	if(Dlg2.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath2[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath2), szDirPath2);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath2);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath2);	// ���� �̸��� ����� ������ ��θ� ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
						L"dat", // ������ Ȯ���ڸ�
						L"*.dat", // ���ʿ� ����� ���� �̸�
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
						this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath);	// ���� �̸��� ����� ������ ��θ� ����
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
						L"dat", // ������ Ȯ���ڸ�
						L"*.dat", // ���ʿ� ����� ���� �̸�
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
						L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
						this);

	if(Dlg2.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath2[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath2), szDirPath2);	// vcproj ���� ��ġ�� ��� ��
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	SetCurrentDirectory(szDirPath2);	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �ٲ��ִ� �Լ�
	// szDirPath = 0x002ef084 "c:\Users\Administrator\Desktop\FrameKor02\ToolKor02"

	PathRemoveFileSpec(szDirPath2);	// ���� �̸��� ����� ������ ��θ� ����
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